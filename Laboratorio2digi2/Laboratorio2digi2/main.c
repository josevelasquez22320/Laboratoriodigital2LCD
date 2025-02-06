/*
//********************************************************************************
/* Universidad del Valle de Guatemala
 * IE3054: Electronica digital 2
 * Autor: Jose Andrés Velásquez García 
 * Laboratorio2digi2.c
 *
 * Created: 5/02/2025 10:24:52
 * Author : josea
 */ 
//********************************************************************************
//libraries
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdint.h>
#include <util/delay.h>
#include "uart/UART.h"
#include "Strings/strings.h"
#include "LCD/LCD.h"
#include "ADCC/ADC.h"

// Global Variables
float sensor1_value = 0;
float sensor2_value = 0;
char buffer1[16];
char buffer2[16];
int counter = 0;
char counter_str[10];
int flag = 1;
volatile char received_byte;

// Function Prototypes
void updateLCD(void);

int main(void) {
	initADC();
	lcd_init();
	lcd_command(0x80);
	lcd_print("S1:   S2:   C:  ");
	initUART(fast, 9600);
	sei();
	
	while (1) {
		sensor1_value = (ADC_CONVERT(0) * 5.0) / 1023.0;
		float_to_string(sensor1_value, buffer1, 2);
		sensor2_value = (ADC_CONVERT(1) * 5.0) / 1023.0;
		float_to_string(sensor2_value, buffer2, 2);
		
		updateLCD();

		while (flag == 1) {
			switch (received_byte) {
				case '+': counter++; flag = 0; break;
				case '-': counter--; flag = 0; break;
				default: flag = 0; break;
				
	
			}
		}
	}
}

void updateLCD(void) {
	lcd_set_cursor(1, 0);
	lcd_print(buffer1);
	lcd_set_cursor(1, 4);
	lcd_print("V");
	
	lcd_set_cursor(1, 6);
	lcd_print(buffer2);
	lcd_set_cursor(1, 10);
	lcd_print("V");
	
	sprintf(counter_str, "%d", counter);
	lcd_set_cursor(1, 12);
	lcd_print(counter_str);
}



ISR (USART_RX_vect) { // Interrupt triggered when a byte is received
	flag = 1;
	received_byte = UDR0;
}
