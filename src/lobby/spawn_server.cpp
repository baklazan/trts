#include <spawn_server.h>
#include <cstdio>
#include<unistd.h>
#include <utils.h>

int SpawnGameServer(std::pair<int, int> *io) {
	int lobby_to_game[2], game_to_lobby[2];
	report_error(pipe(lobby_to_game));
	report_error(pipe(game_to_lobby));
	
	io->first = game_to_lobby[kPipeRead];
	io->second = lobby_to_game[kPipeWrite];
	int pid = fork();
	report_error(pid);
	if (pid == 0) {
		report_error(dup2(lobby_to_game[kPipeRead], STDIN_FILENO));
		report_error(dup2(game_to_lobby[kPipeWrite], STDOUT_FILENO));
		report_error(execl("game", "./game", reinterpret_cast<char*>(NULL)));
	}
	else {
		return pid;
	}
}
