#include <game_loop.h>
#include <cstdio>
#include <algorithm>
#include <string>
#include <chrono>
#include <thread>
#include <message_writer.h>
#include <message_reader.h>
#include <iostream>

constexpr double kTickDurationSeconds = 0.05;
constexpr std::chrono::duration<double> kTickDuration(kTickDurationSeconds);
constexpr std::chrono::duration<double> kMinTickDuration(0.9 * kTickDurationSeconds);
constexpr std::chrono::duration<double> kMaxDelay(4 * kTickDurationSeconds);

void GameLoop(std::pair<int, int> server_io, std::vector<std::pair<int, int>> clients_io) {
	int n_players = clients_io.size();

	int max_fd = -1;
	for (const auto client_io : clients_io) {
		max_fd = std::max(max_fd, std::max(client_io.first, client_io.second));
	}
	
	int server_in = server_io.first;
	int server_out = server_io.second;

	std::ostringstream start_string;
	start_string << n_players << " maps/test.map debug\n";
    WriteBlocking(server_out, start_string.str());

	std::vector<std::string> client_responses(n_players);
	int count_responded;
	std::vector<NonblockingWriter*> writers;
	std::vector<MessageReader*> readers;
	for (int i=0; i<n_players; i++) {
		writers.push_back(new NonblockingWriter(clients_io[i].second));
		auto callback = [i, &client_responses, &count_responded](std::string message){
			client_responses[i] = message;
			count_responded ++;
		};
		readers.push_back(new MessageReader(clients_io[i].first, callback));
	}

    auto t_start = std::chrono::steady_clock::now();
    auto t_next_tick = t_start + kTickDuration;
	while (true) {
        auto t_tick_start = std::chrono::steady_clock::now();
		count_responded = 0;
		std::istringstream command_in(ReadMessageBlocking(server_in));
		std::string command;
		command_in >> command;
		if (command == "tick") {
			int tick_number;
			command_in >> tick_number;
			for (auto writer : writers) {
				writer->AddMessage("tick\n");
				writer->AddMessage(ReadMessageBlocking(server_in));
			}
		}
		else if (command == "end") {
			for (int i=0; i<n_players; i++) {
			    int is_winner;
			    command_in >> is_winner;
				if (is_winner == 1) {
					WriteBlocking(clients_io[i].second, "end win\n");
				}
				else {
					WriteBlocking(clients_io[i].second, "end lose\n");
				}
			}
			break;
		}
		
		while (count_responded < n_players) {
			fd_set read_fd_set, write_fd_set;
			FD_ZERO(&read_fd_set);
			FD_ZERO(&write_fd_set);
			for (int i=0; i<n_players; i++) {
				FD_SET(clients_io[i].first, &read_fd_set);
				if (writers[i]->WantToWrite()) {
					FD_SET(clients_io[i].second, &write_fd_set);
				}
			}
			select(max_fd+1, &read_fd_set, &write_fd_set, NULL, NULL);
			for (int i=0; i<n_players; i++) {
				if (FD_ISSET(clients_io[i].first, &read_fd_set)) {
					readers[i]->Read();
				}
				if (FD_ISSET(clients_io[i].second, &write_fd_set)) {
					writers[i]->Write();
				}
			}
		}
		
		for (const std::string &response : client_responses) {
			WriteBlocking (server_out, response);
		}
		
		auto t_now = std::chrono::steady_clock::now();
		if (max(t_next_tick, t_tick_start + kMinTickDuration) > t_now) {
            auto time_to_wait = max(t_next_tick, t_tick_start + kMinTickDuration) - t_now;
            std::this_thread::sleep_for(time_to_wait);
        }
		t_now = std::chrono::steady_clock::now();
		t_next_tick = std::max(t_next_tick + kTickDuration, t_now + kTickDuration - kMaxDelay);
	}
	
	for (auto writer : writers) {
		delete writer;
	}
	for (auto reader : readers) {
		delete reader;
	}
}
