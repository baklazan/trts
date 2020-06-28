#include <spawn_client.h>
#include <cstdio>
#include <utils.h>
#include <sys/types.h>
#include <unistd.h>


void RedirectAndExec(int new_stdin, int new_stdout) {
	report_error(dup2(new_stdin, STDIN_FILENO));
	report_error(dup2(new_stdout, STDOUT_FILENO));
	report_error(execl("ui", "./ui", reinterpret_cast<char*>(NULL)));
}

int SpawnAndConnectGameClient(sockaddr_in address) {
	int pid = fork();
	report_error(pid);
	if (pid == 0) {
		int loopback_socket = socket(AF_INET, SOCK_STREAM, 0);
		report_error(loopback_socket);
		int err = connect(loopback_socket, reinterpret_cast<sockaddr*>(&address), sizeof(address));
		report_error(err);
		RedirectAndExec(loopback_socket, loopback_socket);
	}
	else {
		return pid;
	}
}

int SpawnGameClient(int fd) {
	int pid = fork();
	report_error(pid);
	if (pid == 0) {
		RedirectAndExec(fd, fd);
	}
	else {
		return pid;
	}
}
