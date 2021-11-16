/*
 * ADC.h
 *
 * Created: 2021-04-25 11:14:47
 * Author: Edvin
 */ 

#ifndef ADC_H_
#define ADC_H_
/**
 @brief	Init for ADC readings. 
   
 @return   None. 
 */
void ADCInit();

/**
 @brief Gets acceleration of an axis. 
 
 @param	axis The wanted axis of acceleration. 	
 @return	 Float containing ambient temperature. 
 */
uint16_t getAcceleration(uint8_t axis);

/**
 @brief	Gets reading from distance sensor. 
   
 @return   Distance from distance sensor. 
 */
uint16_t getDistance();
#endif /* ADC_H */