I start to write arduino tutorial using pure C language.
Please download arduino IDE.
If your arduino doesn't see USB driver, you need to download and install USB-SERIAL CH340 driver.
You can find atmega328p reference manual and pinout diagram for arduino UNO in docs directory,
it can help you to understand this tutorials and you can write your own projects.

Information about project:

gpio/led_blink: simple program that can blink led on pin 9.
		Use PORTB1 and DDRB to init our register.
		Please read reference manual and see look at pinout
		to understand this simple program.

gpio/timer_led_blink: program that based on gpio/led_blink.
			Now we can blinking led with timer and interrupt.
			We init our timer to compare with number in OCR reg
			and if it equal go to ISR() function.

gpio/button: program that based on gpio/led_blink.
		Now we can turn on or off led depending on
		button state.

gpio/interrupt: program that based on gpio/led_blink.
		Now we can toggle led state depending on
		logic level on INT0 using interrupts.

uart/uart_drv: simple uart driver. we can test in with led,
		if we receive 1 - led on and if we receive
		0 - led off.

i2c/i2c_drv: add implemetnation i2c driver. Iw you want to test it,
		plese take you own i2c device and include your program
		in while loop in main function.
