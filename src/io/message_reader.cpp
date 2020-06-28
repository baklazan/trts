#include <message_reader.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <utils.h>
#include <vector>
#include <iostream>

MessageReader::MessageReader(int fd, std::function<void(std::string)> callback) : fd_(fd), callback_(callback) {
	Reset();
};

void MessageReader::Reset() {
	buffer_.clear();
	state_ = READER_STATE_HEADER;
	expecting_bytes_ = 4;
	bytes_in_body_ = 0;
}

void MessageReader::ProcessByte(uint8_t byte) {
	switch(state_) {
		case READER_STATE_HEADER: {
			bytes_in_body_ = bytes_in_body_ | byte << (8 * (expecting_bytes_-1));
			expecting_bytes_ --;
			if (expecting_bytes_ == 0) {
				expecting_bytes_ = bytes_in_body_;
				state_ = READER_STATE_BODY;
			}
			break;
		}
		case READER_STATE_BODY: {
			buffer_.push_back(byte);
			expecting_bytes_ --;
			break;
		}
	}
    if (state_ == READER_STATE_BODY && expecting_bytes_ == 0) {
        callback_(buffer_);
        Reset();
    }
}

int MessageReader::Read() {
	uint8_t buffer[512];
	unsigned total_bytes_read = 0;
	while (true) {
		int bytes_read = ::recv(fd_, buffer, 512, MSG_DONTWAIT);
		if (bytes_read == 0) break;
		if (bytes_read == -1) {
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				break;
			}
			else {
				perror("reading");
				return -1;
			}
		}
		for (int i = 0; i < bytes_read; i++) {
			ProcessByte(buffer[i]);
		}
		total_bytes_read += bytes_read;
	}
	if (total_bytes_read == 0 && rand() % 10 == 0) return -1;
	return 0;
}

void ReadBlocking(int fd, uint8_t *buffer, int count) {
	int read_so_far = 0;
	while (read_so_far < count) {
		int read_now = ::read(fd, &buffer[read_so_far], count-read_so_far);
		report_error(read_now);
		read_so_far += read_now;
	}
}

std::string ReadMessageBlocking(int fd) {
	uint8_t head[4];
	ReadBlocking(fd, reinterpret_cast<uint8_t*>(head), 4);
	uint32_t size = 0;
	for (uint8_t byte : head) {
		size = size << 8;
		size += byte;
	}

	std::vector<char> message(size);
	ReadBlocking(fd, reinterpret_cast<uint8_t*>(message.data()), size);
	std::string result(message.data(), size);
	
	return std::string(result);
}
