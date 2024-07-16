#include "filehelper.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

char *read_file(const char *path) {
  struct stat sb;
  off_t len;
  char *p, *result;
  int fd;

  fd = open(path, O_RDONLY);
  if (fd == -1) {
    perror("open");
    return 0;
  }

  if (fstat(fd, &sb) == -1) {
    perror("fstat");
    return 0;
  }

  if (!S_ISREG(sb.st_mode)) {
    return 0;
  }

  p = mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);

  if (close(fd) == -1) {
    perror("close");
  }

  result = malloc(sb.st_size);
  memcpy(result, p, sb.st_size);

  if (munmap(p, sb.st_size) == -1) {
    perror("munmap");
  }

  return result;
}
