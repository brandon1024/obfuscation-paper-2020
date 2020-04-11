#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "utils.h"

ssize_t recoverable_read(int fd, void *buf, size_t len)
{
	int errsv = errno;

	ssize_t bytes_read = 0;
	while(1) {
		bytes_read = read(fd, buf, len);
		if ((bytes_read < 0) && (errno == EAGAIN || errno == EINTR)) {
			errno = errsv;
			continue;
		}

		break;
	}

	return bytes_read;
}

ssize_t recoverable_write(int fd, const void *buf, size_t len)
{
	int errsv = errno;

	ssize_t bytes_written = 0;
	while(1) {
		bytes_written = write(fd, buf, len);
		if ((bytes_written < 0) && (errno == EAGAIN || errno == EINTR)) {
			errno = errsv;
			continue;
		}

		break;
	}

	return bytes_written;
}