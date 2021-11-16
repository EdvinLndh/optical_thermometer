/*
 * Buzzer.c
 *
 * Created: 2021-04-25 11:14:47
 *  Author: Edvin
 */ 

#include <avr/io.h>
#include "GlobalDefinitions.h"
#include "buzzer.h"
#include <util/delay.h>

/*********************************/
/* Initializes buzzer. 			 */
/*********************************/
void buzzerInit(){
	// Set output port. 
	SETBIT(DDRD, OUTPUT);
	// Set output to low. 
	CLEARBIT(PORTD, OUTPUT);
	// Set timer mode normal and toggle OC0A on compare. 
	TCCR0A = (1 << WGM01) | (1 << COM0A0) ;
	TCCR0B = (1 << CS01) | (1 << CS00);
}


/*****************************************************/
/* Makes summer buzz at given frequency.			 */
/*****************************************************/
void setBuzzer(int freq){
		OCR0A = freq;
}


/*****************************************************************/
/* Plays a melody by playing at different frequencies.			 */
/*****************************************************************/
void playMelody() {
	setBuzzer(100);
	_delay_ms(100);
	setBuzzer(200);
	_delay_ms(100);
	setBuzzer(300);
	_delay_ms(100);
	setBuzzer(400);
	_delay_ms(100);
}
