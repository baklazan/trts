#include <message_writer.h>
#include <unistd.h>
#include <utils.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

MessageWriter::MessageWriter(int fd) : std::ostringstream(), fd_(fd) {}

void MessageWriter::Flush() {
    //std::cerr << "flushing:\n" << str() << std::endl;
	std::string data;
	uint32_t size = str().size();
	for (int i = 24; i >= 0; i-=8) {
		data.push_back((size >> i) & 255);
	}
	data += str();
	WriteBlocking(fd_, data);
	str("");
}

NonblockingWriter::NonblockingWriter(int fd) : fd_(fd), current_position_(0) {}

void NonblockingWriter::AddMessage(std::string message) {
	buffer_.push(message);
}

void NonblockingWriter::Write() {
	if (buffer_.size() > 3) {
		printf("buffer size: %lu\n", buffer_.size());
	}
	while (!buffer_.empty()) {
		const std::string &message = buffer_.front();
		while (current_position_ < message.size()) {
			int written_now = ::send(fd_, &(message[current_position_]), message.size() - current_position_, MSG_DONTWAIT);
			if (written_now == 0) return;
			if (written_now == -1) {
				if (errno != EAGAIN && errno != EWOULDBLOCK) {
					perror("writing");
				}
				return;
			}
			current_position_ += written_now;
		}
		buffer_.pop();
		current_position_ = 0;
	}
}

bool NonblockingWriter::WantToWrite() {
	return !buffer_.empty();
}

void WriteBlocking (int fd, const std::string &message) {
	unsigned written = 0;
	while (written < message.size()) {
		unsigned written_now = ::write(fd, &(message.c_str()[written]), message.size() - written);
		report_error(written_now);
		written += written_now;
	}
}
