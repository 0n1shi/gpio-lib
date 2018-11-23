#include <stdio.h>
#include <unistd.h>

#include "./include/gpio.h"

#define PIN_NUMBER 26

void check_pin_state(int state) {
  if (state == PIN_ON)
    printf("pin (%d) is on\n", PIN_NUMBER);
  else if (state == PIN_OFF)
    printf("pin (%d) is off\n", PIN_NUMBER);
}

int main(int argc, char* argv[])
{
  gpio_init();
  pin_mode(PIN_NUMBER, PIN_MODE_OUT);
  
  /* turn it on and check status */
  pin_on(PIN_NUMBER);
  check_pin_state(pin_read(PIN_NUMBER));
  
  sleep(1);
  
  /* turn it off and check status */
  pin_off(PIN_NUMBER);
  check_pin_state(pin_read(PIN_NUMBER));
  
  gpio_terminate();
  return 0;
}
