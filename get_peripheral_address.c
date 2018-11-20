#include <stdio.h>
#include <bcm_host.h>

int main(int argc, char* argv[]) {
  printf("0x%08X\n", bcm_host_get_peripheral_address());
  return 0;
}
