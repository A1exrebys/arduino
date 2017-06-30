/****************************************************************
 * This is simple blinking led program.
 * You can find register summary in 428 page of
 * atmega328p.pdf and pinout in pinout.png.
 * Led on pin 9, it is PORTB1 and have offset 0x25.
 * Any logical change on INT0 - pin2 invoke IRQ().
 ****************************************************************/
#include <avr/interrupt.h>


/*
 * Define offset to our registers.
 */
#define OFFSET_EICRA    0x69
#define OFFSET_EIMSK    0x3D
#define OFFSET_DDR_B    0x24
#define OFFSET_PORT_B   0x25

/*
 * Mapped
 */
#define EICR_A  *((volatile unsigned char *)OFFSET_EICRA)
#define EIMS_K  *((volatile unsigned char *)OFFSET_EIMSK)
#define DDR_B   *((volatile unsigned char *)OFFSET_DDR_B)
#define PORT_B  *((volatile unsigned char *)OFFSET_PORT_B)

/*
 * Configure DDRB as output
 */
void init_gpio()
{
        DDR_B = 1 << 1;
}

/*
 * Init external interrupt.
 */
void init_int()
{
        /*
         * Clear interrupt flag.
         */
        cli();

        /*
         * Init INT0 change.
         */
        EIMS_K = 1 << 0;
        EICR_A = 1 << 0;

        /*
         * Enable interrupt.
         */
        sei();
}

/*
 * Main function.
 */
int main () {
        /*
         * Init all modules.
         */
        init_gpio();
        init_int();

        /*
         * Infinite loop.
         */
        while (1) {
        }
}

/*
 * Interrupt service routine.
 * Change led state.
 */
ISR(INT0_vect) 
{
        PORT_B ^= 1 << 1;
}
