#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <bcm_host.h>

#include "../include/gpio.h"

unsigned int peripheral_address;
unsigned int gpio_address;
unsigned int address;
int page_size;
int file_descriptor;

int gpio_init(void)
{
  peripheral_address = bcm_host_get_peripheral_address();
  gpio_address = peripheral_address + 0x00200000;

  page_size = getpagesize();
  if (page_size < 0) {
    perror("failed with getpagesize()\n");
    return -1;
  }

  if ((file_descriptor = open(DEVICE_FILE, O_RDWR | O_SYNC)) < 0) {
    perror("failed with open()\n");
    return -1;
  }

  address = (unsigned int)mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, gpio_address);
  if (address == MAP_FAILED) {
    perror("failed with mmap()\n");
    return -1;
  }

  return 0;
}

void gpio_terminate(void)
{
  munmap((void*)address, page_size);
  close(file_descriptor);
  return;
}

int pin_init(int pin_number, int pin_mode)
{
  int num_sel_reg = (pin_number % NUM_SEL_REG) - 1;
  int addr = GPFSEL0_OFFSET + (REG_GAP * num_sel_reg);
  int mode;
  
  if (pin_mode == PIN_MODE_IN) {
    mode = PIN_MODE_IN;
  } else if (pin_mode == PIN_MODE_OUT) {
    mode = PIN_MODE_OUT;
  } else {
    perror("failed to set pin mode. (invalid mode designated)\n");
    return -1;
  }


}
