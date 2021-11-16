/*
 * UART.c
 *
 * Created: 2021-04-21 12:55:06
 * Author : Edvin
 */ 

#include <stdio.h>
#include <avr/io.h>
#include "USART.h"
#include "GlobalDefinitions.h"

#include <util/delay.h>


static int uartPutChar(char c, FILE *stream);
static FILE uartStdout = FDEV_SETUP_STREAM(uartPutChar, NULL, _FDEV_SETUP_WRITE);

void USARTInit(){
	UBRR0H = (BAUD_RATE_9600_BPS >> 8);
	UBRR0L = BAUD_RATE_9600_BPS;
		
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

int uartPutChar(char c, FILE *stream) {
	// Add timeout...
	
	// Do  nothing  until  UDR is  ready  for  more  data to be  written  to it
	while ((UCSR0A & (1 << UDRE0)) == 0);
	// Echo  back  the  received  byte  back to the  computer
	UDR0 = c;
	
	return 0;
}


