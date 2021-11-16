/*
 * IRSensor.c
 *
 * Created: 2021-04-26 18:37:52
 * Author: Edvin
 */ 

#include "i2cmaster.h"
#include "IRSensor.h"
#include "GlobalDefinitions.h"
#include <util/delay.h>

static float averageValue(uint8_t adress);


/*******************************/
/* Initializes IR-sensor.	   */
/*******************************/
void IRinit() {
	// Enable pull up
	PORTC |= (1 << PINC4) | (1 << PINC5);
	i2c_init();
}

/************************************************/
/* Reads current ambient temperature.			*/
/************************************************/
float IRreadAmbientTemp(){

	float ambient = averageValue(TEMPAMBIENT);
	
	return ((ambient / 50) - 273);
}


/************************************************/
/* Reads temperature of object.					*/
/************************************************/
float IRreadObjectTemp(){

		float object = averageValue(TEMPOBJECT);
		
		return ((object / 50) - 273);
}


/********************************************************************************/
/* Averages the reading of the IR-sensor by adding the readings and dividing	*/
/* by the sample size.                                                          */
/********************************************************************************/
static float averageValue(uint8_t adress){

	float input = 0;

	for(int i = 0; i < SAMPLESIZE; i++) {
		// Write to slave
		i2c_start(SLAVE_ADRESS + I2C_WRITE);
		
		i2c_write(adress);
		
		i2c_rep_start(SLAVE_ADRESS + I2C_READ);
		
		// Read temperature. 
		uint8_t lowByte = i2c_readAck();
		uint8_t highByte = i2c_readAck();
		uint8_t pec = i2c_readNak();

		i2c_stop();
		
		// Add numbers. 		
		input += ((uint16_t)highByte << 8) | lowByte;
		
		// Wait a bit.
		_delay_ms(1);
	}

	return input/SAMPLESIZE;
}