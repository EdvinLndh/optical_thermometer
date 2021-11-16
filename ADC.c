/*
 * ADC.c
 *
 * Created: 2021-04-25 11:14:47
 * Author: Edvin
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "GlobalDefinitions.h"
#include "ADC.h"

static uint16_t averageValue();

/***********************************************/
/*  Gets reading from distance sensor.         */
/***********************************************/
uint16_t getDistance(){

	// Set ADMUX
	ADMUX = (1 << REFS0) | (1 << MUX1) | (1 << MUX0);	

	uint16_t distance = averageValue();

	return (distance / 31); 
}

/********************************************/
/* Gets acceleration of an axis.			*/
/********************************************/
uint16_t getAcceleration(uint8_t axis){

	ADMUX = axis; 
		
	uint16_t acc = averageValue();

	return (acc / 31); 
}

/****************************************/
/* Init for ADC readings.               */
/****************************************/
void ADCInit(){
	 
	//ADC enabled & division set. 8 Mhz/128 => 62 kHz ADclock.
	ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	
	//AVcc ref, ADC0 (= PC0) as single ended input
	ADMUX = (1 << REFS0);

}

/********************************************/
/* Averages value of ADC reading.			*/
/********************************************/
static uint16_t averageValue(){

	uint16_t input = 0; 

	for(int i = 0; i < SAMPLESIZE; i++) {
		// Start conversion.
		ADCSRA |= (1<<ADSC);
	
		// Wait until done. INSERT TIMEOUT
		while((ADCSRA & (1 << ADSC)) != 0);
		
		input += ADC; 	
		
		// Wait a bit.
		_delay_ms(1);
	} 

	return input/SAMPLESIZE; 
}