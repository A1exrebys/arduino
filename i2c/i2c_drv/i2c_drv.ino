/****************************************************************
 * This is i2c driver. You can check it with your own i2c device.
 * You can find register summary in 428 page of
 * atmega328p.pdf and pinout in pinout.png.
 ****************************************************************/
#include <avr/io.h>

#define I2C_BASE	0xB8
#define PORT_B		0x25
#define DDR_B		0x24

#define BIT_OFF          3
#define SIZE_OFF         1

struct i2c_reg {
  	unsigned char twbr;
  	unsigned char twsr;
  	unsigned char twar;
  	unsigned char twdr;
  	unsigned char twcr;
  	unsigned char twamr;
};

volatile static struct i2c_reg *reg = (void *)I2C_BASE;

/*
 * Init I2C module
 */
void i2c_init()
{
  	reg->twbr = 0x48;
  	reg->twsr = 0x00;
}

/*
 * Send START condition and addres + R/W
 */
int i2c_start (unsigned char addr)
{
 	/*  
   	 * Clean register
   	 */
  	reg->twcr = 0;
  
  	/*  
   	 * Send START condition
   	 */
  	reg->twcr = (1 << 7) | (1 << 5) | (1 << 2);

 	/*
    	 * Wait that START condition transmitted
    	 */
   	while (!(reg->twcr & (1 << 7)));

    	/*
     	 * Check if we received ACK START
     	 */
     	if ((reg->twsr & 0xF8) != 0x08)
      		      return 1;

    	/*
    	 * Load addr
    	 */
   	reg->twdr = addr;
   
   	reg->twcr |= (1 << 7) | (1 << 2);

   	while (!(reg->twcr & (1 << 7)));

   	if (((reg->twsr & 0xF8) != 0x18) && ((reg->twsr & 0xF8) != 0x40))
            	return 2;

    	return 0;
}

/*  
 * Send STOP to I2C
 */
void i2c_stop()
{
	/*  
   	 * Send STOP condition
   	 */
   	reg->twcr = (1 << 7) | (1 << 4) | (1 << 2); 
}

/*
 * Write one character to I2C
 */
int i2c_write(unsigned char buf)
{
	/*
	 * Write DATA
	 */
  	reg->twdr = buf;

   	reg->twcr = (1 << 7) | (1 << 2);

   	/*
	   * Wait until it transmit
	   */
   	while (!(reg->twcr & (1 << 7)));

   	/*
	 * Check if we receive DATA ACK
	 */
   	if ((reg->twsr & 0xF8) != 0x28)
      		return 1;

   	return 0;
}

/*
 * Write one character from I2C
 */
void i2c_read(unsigned char *buf)
{
	reg->twcr = (1 << 7) | (1 << 2);

      	while (!(reg->twcr & (1 << 7)));
      
     	*buf = reg->twdr; 
}

int main()
{
	while (1) {
	}
}
