/****************************************************************
 * This is simple blinking led program.
 * You can find register summary in 428 page of
 * atmega328p.pdf and pinout in pinout.png.
 * Led on pin 9 if we receive 1 - led on, if 0 - led off.
 * IT IS OUR UART DRIVER
 ****************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BAUDRATE         9600
#define FOSC             16000000UL
#define UBBR             (FOSC/(16UL*BAUDRATE)) - 1

#define TX_OFF           3
#define RX_OFF           4

#define BIT_OFF          3
#define SIZE_OFF         1

#define UART_BASE	0xC0

struct uart_reg {
	unsigned char ucsr_a;
	unsigned char ucsr_b;
	unsigned char ucsr_c;
	unsigned char res;
	unsigned char ubr_l;
	unsigned char ubr_h;
	unsigned char udr;
};

volatile struct uart_reg *reg = (void *)UART_BASE;

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
 * Configure DDRB as output
 */
void init_gpio()
{
	DDR_B = 1 << 1;
}

/*
 * Write to PORTB 1 << 1;
 */
void led_on()
{
	PORT_B = 1 << 1;
}

/*
 * Write to PORTB 0 << 1;
 */
void led_off()
{
	PORT_B = 0 << 1;
}

/*
 * Init UART register
 */
void init_uart()
{
	/*
	 * Init baudrate
	 */
        reg->ubr_h = (unsigned char)(UBBR >> 8);
        reg->ubr_l = (unsigned char)UBBR;

        /*
         * Init TX and RX
         */
        reg->ucsr_b = (1 << TX_OFF) | (1 << RX_OFF) | (1 << 7);
        reg->ucsr_c = 0x06;

        /*
         * Enable interrupt
         */
        sei();
}

/*
 * Trans one character via UART
 */
void uart_trans(unsigned char data)
{
	while (!(reg->ucsr_a & (1 << 5)))
		;

	reg->udr = data;
}

/*
 * Receive one character via UART
 */
unsigned char uart_recv()
{
	while (!(reg->ucsr_a & (1 << 7)))
		;

	return  reg->udr;
}

/*********************************************************************
 * TEST OUR UART DRIVER
 ********************************************************************/
/*
 * Check numbers
 */
void check_buf(unsigned char buf)
{
	unsigned int num;

	/*
	 * Check if we receive numbers
	 */
	if (buf >= 0x30 && buf <= 0x39) {
		uart_trans(buf);

		num = buf - 0x30;

		if (num == 0)
			led_off();

		if (num == 1)
			led_on();
        }
}

/*
 * Main Loop
 */
int main() {
	unsigned char data[23] = "Please enter number : ";
	int i;

	init_uart();
	init_gpio();

	for (i = 0; i < 23; i++)
		uart_trans(data[i]);

	while (1) {
	}
}

ISR(USART_RX_vect)
{
	check_buf(reg->udr);
}