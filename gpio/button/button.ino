/****************************************************************
 * This is simple blinking led program.
 * You can find register summary in 428 page of
 * atmega328p.pdf and pinout in pinout.png.
 * Led on pin 9, it is PORTB1 and have offset 0x25.
 ****************************************************************/
#include <util/delay.h>

/*
 * Define offset to our registers.
 */
#define OFFSET_PIN_B   	0x23
#define OFFSET_DDR_B   	0x24
#define OFFSET_PORT_B 	0x25

/*
 * Mapped it.
 */
#define PIN_B 	*((volatile unsigned char *)OFFSET_PIN_B)
#define DDR_B 	*((volatile unsigned char *)OFFSET_DDR_B)
#define PORT_B 	*((volatile unsigned char *)OFFSET_PORT_B)

/*
 * Configure DDRB1 as output and DDRB0 as input.
 */
void init_gpio()
{
	DDR_B = 1 << 1;
	DDR_B |= ~(1 << 0);
}

/*
 * Led on.
 */
void led_on()
{
	PORT_B = 1 << 1;
}

/*
 * Led off.
 */
void led_off()
{
	PORT_B = 0 << 1;
}

/*
 * Main function.
 */
int main()
{
	/*
	 * Init module.
	 */
	init_gpio();

	/*
	 * Infinite loop.
	 */
	while (1) {
		if (PIN_B & 0x01)
			led_on();
		else
			led_off();
	}
}
