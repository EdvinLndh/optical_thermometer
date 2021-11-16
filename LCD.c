/*
 * LCD.c
 *
 * Created: 2021-04-21 12:14:00
 * Author : Edvin
 */ 

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <util/delay.h>
#include "LCD.h"
#include "GlobalDefinitions.h"

static void DisplayInit();
static void SPIInit();

/************************************************/
/* Sends instruction via SPI to LCD.            */
/************************************************/
void spi_tx(int8_t instruction) {

		// Select slave.
		CLEARBIT(PORTB, 2);
		// Clear RS bit.
		CLEARBIT(PORTB, 1);
		// Load instruction.
		SPDR = instruction;
		// Loop until transfer complete.  
		while(!(SPSR & (1 << SPIF)));
		// Deselect slave. 
		SETBIT(PORTB, 2); 

		return;
}

/****************************************/
/* Initializes SPI communication.       */
/****************************************/
static void SPIInit(){
	
	// SPI INIT
	DDRB |= (1 << PINB1) | (1 << PINB2) | (1 << PINB3) | (1 << PINB5);
	
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	
	return;
}

/****************************************/
/* Initializes LCD via SPI.             */
/****************************************/
static void DisplayInit(){
		// LCD INIT
		
		// Send instructions...
		spi_tx(FUNCTION_SET);
		_delay_us(DELAY_US);
		
		spi_tx(BIAS_SET);
		_delay_us(DELAY_US);
		
		spi_tx(POWER_CONTROL);
		_delay_us(DELAY_US);
		
		spi_tx(FOLLOWER_CONTROL);
		_delay_us(DELAY_US);
		
		spi_tx(CONTRAST_SET);
		_delay_us(DELAY_US);
		
		spi_tx(FUNCTION_SET_2);
		_delay_us(DELAY_US);
		
		spi_tx(DISPLAY_ON);
		_delay_us(DELAY_US);
		
		spi_tx(CLEAR_DISPLAY);
		_delay_ms(DELAY_MS);
		
		spi_tx(ENTRY_MODE_SET);
		_delay_us(DELAY_US);
		
}

/***************************************************************************/
/* Initialize LCD by enabling SPI and sending instructions to display.     */
/***************************************************************************/
void LCDInit(){
	SPIInit();
	DisplayInit();
}


