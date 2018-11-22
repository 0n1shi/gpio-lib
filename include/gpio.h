#ifndef GPIO_H
#define GPIO_H

#define GPFSEL0_OFFSET 0x0000
#define GPSET0_OFFSET 0x001C
#define GPCLR0_OFFSET 0x0028
#define GPLEV0_OFFSET 0x0034

#define NUM_SEL_REG 5
#define NUM_PIN_EACH_REG 10
#define REG_GAP 4

#define DEVICE_FILE "/dev/mem"
#define MEMORY(addr) (*((volatile unsigned int*)(addr)))

#define PIN_MODE_IN 0b000
#define PIN_MODE_OUT 0b001

#define SEL(num, mode) (mode << (num * 3))
#define SET(num) (1 << num)
#define CLR(num) (1 << num)

extern unsigned int peripheral_address;
extern unsigned int gpio_address;

extern int file_descriptor;
extern unsigned int address;

extern int page_size;

extern int gpio_init(void);
extern void gpio_terminate(void);
extern void pin_mode(unsigned int pin_number, int mode);
extern void pin_on(unsigned int pin_number);
extern void pin_off(unsigned int pin_number);

#endif
