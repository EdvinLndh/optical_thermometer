#define DELAY_US 30
#define DELAY_MS 2
#define FUNCTION_SET 0b00111001
#define BIAS_SET 0b00010101
#define POWER_CONTROL 0b01010101
#define FOLLOWER_CONTROL 0b01101110
#define CONTRAST_SET 0b01110010
#define FUNCTION_SET_2 0b00111000
#define DISPLAY_ON 0b00001111
#define CLEAR_DISPLAY 0b00000001
#define ENTRY_MODE_SET 0b00000110
#define RETURN_HOME 0b00000011



#ifndef LCD_H_
#define LCD_H_
/**
 @brief Initialize LCD by enabling SPI and sending instructions to display. 
 
 @return   none
 */
void LCDInit();

/**
 @brief	 Sends instruction via SPI to LCD.  
 
 @return   none
 */
void spi_tx(int8_t instruction);
#endif /* LCD_H_ */