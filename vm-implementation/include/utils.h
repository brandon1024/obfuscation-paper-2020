#ifndef B64_ENCODER_VM_OBFUSCATED_UTILS_H
#define B64_ENCODER_VM_OBFUSCATED_UTILS_H

#include <sys/types.h>

ssize_t recoverable_read(int fd, void *buf, size_t len);
ssize_t recoverable_write(int fd, const void *buf, size_t len);

#endif //B64_ENCODER_VM_OBFUSCATED_UTILS_H
