#ifndef GPIO_H
#define GPIO_H

#define GPFSEL0_OFFSET 0x0000
#define GPSET0_OFFSET 0x001C
#define GPCLR0_OFFSET 0x0028
#define GPLEV0_OFFSET 0x0034

#define NUM_SEL_REG 5
#define REG_GAP 4

#define DEVICE_FILE "/dev/mem"
#define MEMORY(addr) (*((volatile unsigned int*)(addr)))

#define SEL_IN(n) (0b000 << (n * 3))
#define SEL_OUT(n) (0b001 << (n * 3))
#define SET(n) (1 << n)
#define CLR(n) (1 << n)

#define PIN_MODE_IN 0b000
#define PIN_MODE_OUT 0b001

extern unsigned int peripheral_address;
extern unsigned int gpio_address;

extern int file_descriptor;
extern unsigned int address;

extern int page_size;

extern int gpio_init(void);
extern void gpio_terminate(void);
extern int gpio_set(int pin_number, int pin_mode);

#endif
