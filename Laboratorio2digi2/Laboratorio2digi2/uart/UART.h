/*
 * UART.h
 *
 * Created: 6/02/2025 11:01:46
 *  Author: josea
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>  
#include <stdint.h>  

#define fast 1        // Define macro for fast UART mode
#define no_fast 0     // Define macro for non-fast (standard) UART mode

// Function to initialize UART with configurable speed and baud rate
void initUART(uint8_t Fast, uint16_t BaudRate);

// Function to transmit a single character over UART
void write_UART(char caracter);

// Function to transmit a string (null-terminated) over UART
void txt_write_UART(char* cadena);

// Function to read a character from UART (returns 0 if no data is available)
unsigned char read_UART(void);




#endif /* UART_H_ */