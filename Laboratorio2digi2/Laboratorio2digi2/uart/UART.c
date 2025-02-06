/*
 * UART.c
 *
 * Created: 6/02/2025 11:01:34
 *  Author: josea
 */ 
#include "UART.h"

// Initialize UART communication with configurable speed and baud rate
void initUART(uint8_t Fast, uint16_t BaudRate){
	// CONFIGURE RX AND TX PINS
	DDRD &=~(1 << DDD0);  // Set RX (PD0) as input
	DDRD |= (1 << DDD1);   // Set TX (PD1) as output
	UCSR0A = 0;            // Clear UCSR0A register
	
	if (Fast){
		// CONFIGURE FAST MODE (U2X0 = 1)
		UCSR0A |= (1 << U2X0);
		if (BaudRate == 9600){
			UBRR0 = 207;  // UBRR0 value for 9600 baud rate with fast mode enabled
		}
		} else {
		// CONFIGURE STANDARD MODE (U2X0 = 0)
		UCSR0A = 0;
		if (BaudRate == 9600){
			UBRR0 = 103;  // UBRR0 value for 9600 baud rate with standard mode
		}
	}
	
	// CONFIGURE UCSR0B REGISTER 
	UCSR0B = 0;
	UCSR0B |= (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);  // Enable RX interrupt, RX and TX

	// CONFIGURE FRAME FORMAT 
	UCSR0C = 0;
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);  // Set frame size to 8 data bits
}

// Function to transmit a single character over UART
void write_UART(char caracter){
	// Wait until the transmit buffer is empty
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = caracter;  // Send the character
}

// null-terminated string
void txt_write_UART(char* cadena){  // Input: null-terminated string 
	while(*cadena != 0x00){
		write_UART(*cadena);  // Transmit each character
		cadena++;  // Move to the next character in the string
	}
}

// returns 0 if no data is available
unsigned char read_UART(void){
	// UDRE0 is set
	if ((UCSR0A & (1 << UDRE0))){
		return UDR0;  // Return received character
		} else {
		return 0;  // Return 0 if no data is available
	}
}
