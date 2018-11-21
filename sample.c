#include <stdio.h>

#include "./include/gpio.h"

int main(int argc, char* argv[])
{
  gpio_init();
  pin_init(4, PIN_MODE_OUT);
  pin_write(4);
  gpio_terminate();
  return 0;
}
