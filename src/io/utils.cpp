#include <utils.h>
#include <cstdio>
#include <cstdlib>

void report_error(int err) {
	if (err == -1) {
		perror("");
		exit(1);
	}
}
