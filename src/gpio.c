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
  gpio_address = peripheral_address + RELATIVE_GPIO_ADDRESS;
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

void pin_mode(unsigned int pin_number, int mode)
{
  int num_reg = (pin_number / NUM_PIN_EACH_SEL_REG);
  int offset = (pin_number % NUM_PIN_EACH_SEL_REG);
  int addr = address + GPFSEL0_OFFSET + (REG_GAP * num_reg);
  MEMORY(addr) = SEL(offset, mode);
  return;
}

void pin_on(unsigned int pin_number)
{
  int num_reg = (pin_number / NUM_PIN_EACH_REG);
  int offset = (pin_number % NUM_PIN_EACH_REG);
  int addr = address + GPSET0_OFFSET + (REG_GAP * num_reg);
  MEMORY(addr) = SET(offset);
  return;
}

void pin_off(unsigned int pin_number)
{
  int num_reg = (pin_number / NUM_PIN_EACH_REG);
  int offset = (pin_number % NUM_PIN_EACH_REG);
  int addr = address + GPCLR0_OFFSET + (REG_GAP * num_reg);
  MEMORY(addr) = CLR(offset);
  return;
}

int pin_read(unsigned int pin_number)
{
  int num_sel_reg = (pin_number / NUM_PIN_EACH_REG);
  int offset = (pin_number % NUM_PIN_EACH_REG);
  int addr = address + GPLEV0_OFFSET + (REG_GAP * num_sel_reg);
  unsigned int value = MEMORY(addr);
  return ((value >> offset) & 1UL);
}
