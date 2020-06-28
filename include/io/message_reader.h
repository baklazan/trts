#ifndef TRTS_MESSAGE_READER_H
#define TRTS_MESSAGE_READER_H
#include <string>
#include <functional>
#include <unistd.h>


enum MessageReaderState {READER_STATE_HEADER, READER_STATE_BODY};

class MessageReader {
private:
	MessageReaderState state_;
	int expecting_bytes_;
	std::string buffer_;
	unsigned bytes_in_body_;
	
	int fd_;
	std::function<void(std::string)> callback_;
	
	void ProcessByte(uint8_t byte);
	void Reset();
	
public:
	MessageReader(int fd, std::function<void(std::string)> callback);
	int Read();
};

std::string ReadMessageBlocking(int fd);

#endif
