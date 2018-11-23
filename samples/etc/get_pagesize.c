#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  int page_size;
  
  page_size = getpagesize();
  if (page_size < 0) {
    fprintf(stderr, "failed to get page size.\n");
    return -1;
  }

  printf("page size is %dKB\n", page_size);
  return 0;
}
