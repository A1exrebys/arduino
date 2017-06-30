/****************************************************************
 * This is blinking led program using timer.
 * You can find register summary in 428 page of
 * atmega328p.pdf and pinout in pinout.png.
 * Led on pin 9, it is PORTB1 and have offset 0x25.
 * ocr_1x - OUTPUT COMPARE REGISTER - init in it value to compare
 * tccr - init in it timer prescaler and init OCR1A
 * TIMSK - TIMER COUNTER INTERRUPT MASK - enable
 * Timet/Counter Output Compare A.
 ****************************************************************/
#include <avr/io.h>
#include <util/delay.h>

/*
 * Define constant.
 */
#define WGWM_OFF        3
#define ICIE_OFF        1
#define PRESC           0x5
#define VALUE           0x1111

/*
 * Define register offset.
 */
#define TIMER_OFFSET    0x80
#define TIMSK_OFFSET    0x6F
#define OFFSET_DDR_B    0x24
#define OFFSET_PORT_B   0x25

/*
 * Mapped it.
 */
#define TIMSK_REG       *((volatile unsigned char *)TIMSK_OFFSET)
#define DDR_B           *((volatile unsigned char *)OFFSET_DDR_B)
#define PORT_B          *((volatile unsigned char *)OFFSET_PORT_B)

/*
 * Timer registers.
 */
struct timer_reg {
        unsigned char tccr_1a;
        unsigned char tccr_1b;
        unsigned char tccr_1c;
        unsigned char reserved;
        unsigned char tccr_1l;
        unsigned char tccr_1h;
        unsigned char icr_1l;
        unsigned char icr_1h;
        unsigned char ocr_1l;
        unsigned char ocr_1h;
};

volatile struct timer_reg *reg = (void *)TIMER_OFFSET;

/*
 * Init timer
 */
void init_timer()
{
        /*
         * Disable interrupt.
         */
        cli();

        /*
         * Clear registers.
         */
        reg->tccr_1a = 0;
        reg->tccr_1b = 0;
        reg->tccr_1l = 0;
        reg->tccr_1h = 0;

        /*
         * Init ocr register.
         */
        reg->ocr_1h = VALUE >> 8;
        reg->ocr_1l = VALUE & 0x00FF;

        /*
         * Init timer register.
         */
        reg->tccr_1b |= 1 << WGWM_OFF;
        reg->tccr_1b |= 1 << 2;
        reg->tccr_1b |= 1 << 0;

        TIMSK_REG |= 1 << ICIE_OFF;

        /*
         * Enable interrupt.
         */
        sei();
}

/*
 * We need to configure our register as output.
 */
void init_gpio()
{
        DDR_B = 1 << 1;
}

/*
 * Switch PORT state
 */
void led_switch()
{
        PORT_B ^= 1 << 1;
}

/*
 * Main function
 */
int main()
{
	/*
	 * Init our modules.
	 */
	init_timer();
	init_gpio();

        /*
         * Infinite loop
         */
        while (1) {
        }
}

/*
 * Interrupt service routine
 */
ISR(TIMER1_COMPA_vect)
{
	led_switch();
}