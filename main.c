/*
 * main - Optical thermometer.
 *
 * Created: 2021-04-22 14:19:23
 * Author : Edvin
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include "LCD.h"
#include "USART.h"
#include "ADC.h"
#include "main.h"
#include "GlobalDefinitions.h"
#include "buzzer.h"
#include "IRSensor.h"

#define OUTPUTGREEN PINB0
#define OUTPUTRED PIND7
#define XAXIS (1 << REFS0)
#define YAXIS (1 << REFS0) | (1 << MUX0)
#define ZAXIS (1 << REFS0) | (1 << MUX1) 
#define DET PINB7

void init();
static int LCDPutChar(char c, FILE *stream);
static FILE LCDstdout = FDEV_SETUP_STREAM(LCDPutChar, NULL, _FDEV_SETUP_WRITE);
static bool checkCorrectAcceleration(uint8_t x, uint8_t y, uint8_t z);
static bool checkCorrectDistance(uint8_t distance);


/********************************************************/
/*  Put character on LCD screen, used by printf.        */
/********************************************************/
static int LCDPutChar(char c, FILE *stream){
	// Select slave.
	CLEARBIT(PORTB, 2);
	// Set RS bit.
	SETBIT(PORTB, 1);
	// Add timeout...
	while((SPSR & (1 << SPIF)) == 0);
	SPDR = c;
	
	// Deselect slave.
	CLEARBIT(PORTB, 2);
	
	return 0;
}

/********************************************/
/* Checks if the device is upright.			*/
/********************************************/
static bool checkCorrectAcceleration(uint8_t x, uint8_t y, uint8_t z) {
	return ((x >= 15 || x <= 17) && y <= 14 && z <= 18);
}

/************************************************************************/
/* Checks if the object is the correct distance from device.			*/
/************************************************************************/
static bool checkCorrectDistance(uint8_t distance) {
	return (distance <= 30 && distance >= 28);
}


/********************************/
/* Initialize device.			*/
/********************************/
void init(){
	
	DDRB |= (1 << OUTPUTGREEN);
	DDRD |= (1 << OUTPUTRED);
	
	CLEARBIT(DDRB, 7);
	SETBIT(PORTB, 7);
	
	// Init sensors. 
	USARTInit();
	LCDInit();
	ADCInit();
	IRinit();
	buzzerInit();
	
	
	// Set LCD to stdout.
	stdout = &LCDstdout;

	return; 
}

/********************************************************/
/*  Writes ambient and object temperature on LCD        */
/********************************************************/
static void writeTemp()
{
		// Show temperatures on display.
		float ambient = IRreadAmbientTemp();
		uint8_t intPart = (int) ambient;
		float decPart = ambient - intPart;
		int temp = decPart * 10;
	
	
		printf("Ambient = %d.%d  ", intPart, temp);

		float object = IRreadObjectTemp();

		intPart = (int) object;
		decPart = object - intPart;
		temp = decPart * 10;
		printf("Body temp = %d.%d", intPart, temp);

}

/****************************************/
/* Main function of program             */
/****************************************/
int main(void)
{
	init();	
	
    while (1) 
    {	
		
		bool tempIsRead = false;
		int counter = 1000; 
		// Read accelerometer. 
		uint16_t accX = getAcceleration(XAXIS);
		uint16_t accY = getAcceleration(YAXIS);
		uint16_t accZ = getAcceleration(ZAXIS);
		
		// Check if the device is upright.
		while(checkCorrectAcceleration(accX, accY, accZ)) {
			
			// Check if device is still upright, and hasn't read temperature yet. 
			while(checkCorrectAcceleration(accX, accY, accZ) && !tempIsRead) {

					// If upright, get distance
					uint16_t dist = getDistance();
					
					// Check if the distance to forehead is correct.
					if(checkCorrectDistance(dist)){
						
						// Disable red lamp.
						CLEARBIT(PORTD, 7);
						// Start green lamp.
						SETBIT(PORTB, 0);
						
						if(counter == 1500) {
							writeTemp();
							// Make buzzer sound.
							playMelody();						
							tempIsRead = true;
							setBuzzer(0);
						}
						else {
							counter += 10;
							setBuzzer(counter);
							
						}
					}
					// Else, the object is either too far, or too close.
					else {
						counter = 1000; 
						SETBIT(PORTD, 7);
						CLEARBIT(PORTB, 0);
						setBuzzer(2000);
					}

				
					// Read accelerometer. 
					accX = getAcceleration(XAXIS);
					accY = getAcceleration(YAXIS);
					accZ = getAcceleration(ZAXIS);
	
			}
				// Reset counter. 
				counter = 1000; 
				// Read accelerometer. 
				accX = getAcceleration(XAXIS);
				accY = getAcceleration(YAXIS);
				accZ = getAcceleration(ZAXIS);
			
		}
		// Turn off buzzer. 
		setBuzzer(0);
		_delay_ms(2000);
		
		// Turn off diods. 
		CLEARBIT(PORTB, 0);
		CLEARBIT(PORTD, 7);
		
		// For some reason instructions must be sent a few times to LCD 
		// to work, hence the weird for loop... 
		for(int i = 0; i < 5; i++) {
			// Clear screen. 
			spi_tx(CLEAR_DISPLAY);
			_delay_ms(DELAY_MS);
						
		}
    }
}

