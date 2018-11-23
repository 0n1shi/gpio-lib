#ifndef GPIO_H
#define GPIO_H

#define GPFSEL0_OFFSET 0x0000 /* GPIO Function Select Registers (GPFSELn) */
#define GPSET0_OFFSET 0x001C /* GPIO Pin Output Set Registers (GPSETn) */
#define GPCLR0_OFFSET 0x0028 /* GPIO Pin Output Clear Registers (GPCLRn) */
#define GPLEV0_OFFSET 0x0034 /* GPIO Pin Level Registers (GPLEVn) */

#define NUM_PIN_EACH_SEL_REG 10 /* the number of pins in each SEL register */
#define NUM_PIN_EACH_REG 32 /* the number of pins in each register */
#define REG_GAP 4
#define RELATIVE_GPIO_ADDRESS 0x00200000

#define DEVICE_FILE "/dev/mem"
#define MEMORY(addr) (*((volatile unsigned int*)(addr)))

#define PIN_MODE_IN 0b000
#define PIN_MODE_OUT 0b001

#define PIN_ON 1
#define PIN_OFF 0

#define SEL(num, mode) (mode << (num * 3))
#define SET(num) (1 << num)
#define CLR(num) (1 << num)

extern unsigned int peripheral_address; /* address where mapped peripheral registers start */
extern unsigned int gpio_address; /*  */

extern int file_descriptor;
extern unsigned int address;

extern int page_size;

extern int gpio_init(void);
extern void gpio_terminate(void);
extern void pin_mode(unsigned int pin_number, int mode);
extern void pin_on(unsigned int pin_number);
extern void pin_off(unsigned int pin_number);
extern int pin_read(unsigned int pin_number);

#endif
