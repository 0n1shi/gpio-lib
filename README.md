# GPIO library for study

# Sample

```c
#include <stdio.h>
#include <unistd.h>

#include "./include/gpio.h"

int main(int argc, char* argv[])
{
  gpio_init();
  pin_mode(4, PIN_MODE_OUT);
  pin_on(4);
  sleep(1);
  pin_off(4);
  gpio_terminate();
  return 0;
}
```

# Compile

ex.

```bash
gcc main.c src/gpio.c -I/opt/vc/include -L/opt/vc/lib -lbcm_host -Wimplicit-function-declaration
```
