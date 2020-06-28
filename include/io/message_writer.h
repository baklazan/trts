#ifndef TRTS_MESSAGE_WRITER_H
#define TRTS_MESSAGE_WRITER_H
#include <sstream>
#include <queue>

class MessageWriter : public std::ostringstream {
private:
	int fd_;
public:
	MessageWriter(int fd);
	void Flush();
};

class NonblockingWriter {
private:
	int fd_;
	std::queue<std::string> buffer_;
	int current_position_;
public:
	NonblockingWriter(int fd);
	void AddMessage(std::string message);
	void Write();
	bool WantToWrite();
};

void WriteBlocking (int fd, const std::string &message);

#endif
