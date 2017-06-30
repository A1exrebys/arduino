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
#define OFFSET_DDR_B   	0x24
#define OFFSET_PORT_B 	0x25

/*
 * Mapped
 */
#define DDR_B 	*((volatile unsigned char *)OFFSET_DDR_B)
#define PORT_B 	*((volatile unsigned char *)OFFSET_PORT_B)

/*
 * We need to configure our register as output.
 */
void init_gpio()
{
	DDR_B = 1 << 1;
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
 * Main function
 */
int main()
{
	/*
	 * Init our register.
	 */
	init_gpio();

	/*
	 * Infinite loop. Out program must be there.
	 */
	while (1) {
		_delay_ms(500);
		led_on();
		_delay_ms(500);
		led_off();
	}
}
