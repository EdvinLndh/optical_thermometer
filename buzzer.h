/*
 * buzzer.h
 *
 * Created: 2021-04-25 11:27:34
 *  Author: Edvin
 */ 

#define OUTPUT PIND6


#ifndef BUZZER_H_
#define BUZZER_H_

/**
 @brief Initializes buzzer. 
 
 @return   none
 */
void buzzerInit();

/**
 @brief Starts/stops buzzer.
   
 @param     buzzer	Starts/stops buzzer. Start if 1, stops if 0. 
			freq	Buzzing frequency. 
 @return   none
 */
void setBuzzer(int freq);

/**
 @brief Plays a melody by playing at different frequencies. 
   
 @return   none
 */
void playMelody(); 

#endif /* BUZZER_H_ */