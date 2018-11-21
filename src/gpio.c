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

// pin_init(3, PIN_MODE_OUT);
void pin_init(unsigned int pin_number, int mode)
{
  int num_reg = (pin_number / 10);
  int offset = (pin_number % 10);
  int addr = gpio_address + GPFSEL0_OFFSET + (REG_GAP * num_reg);
  MEMORY(addr) = SEL(offset, mode);
  return;
}

void pin_write(unsigned int pin_number)
{
  int num_reg = (pin_number / 32);
  int offset = (pin_number % 32);
  int addr = gpio_address + GPSET0_OFFSET + (REG_GAP * num_reg);
  MEMORY(addr) = SET(offset);
  return;
}

/*
void gpio_read(unsigned int pin_number)
{
  int num_sel_reg = (pin_number / 32);
  int offset = (pin_number % 32);
  int addr = gpio_address + GPLEV0_OFFSET + (REG_GAP * num_sel_reg);

  MEMORY(addr) = SET(offset);
  return;
}

int pin_init(int pin_number, int pin_mode)
{
  int num_sel_reg;
  int addr;
  int mode;
  
  if (pin_mode == PIN_MODE_IN) {
    mode = PIN_MODE_IN;
    num_sel_reg = (pin / 32);
    addr = gpio_address + GPFSEL0_OFFSET + (REG_GAP * num_sel_reg);
  } else if (pin_mode == PIN_MODE_OUT) {
  } else {
    perror("failed to set pin mode. (invalid mode designated)\n");
    return -1;
  }
}
*/
