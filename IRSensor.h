/*
 * IRSensor.h
 *
 * Created: 2021-04-27 09:29:20
 *  Author: Edvin
 */ 


#ifndef IRSENSOR_H_
#define IRSENSOR_H_

#define SLAVE_ADRESS 0x00
#define TEMPAMBIENT 0x06
#define TEMPOBJECT 0x07

/**
 @brief Initializes IR sensor. 

 @return   none
 */
void IRinit();

/**
 @brief Reads the current ambient temperature.
   
 @return   Float containing ambient temperature. 
 */
float IRreadAmbientTemp();

/**
 @brief Reads the current object temperature.
   
 @return   Float containing object temperature. 
 */
float IRreadObjectTemp();


#endif /* IRSENSOR_H_ */