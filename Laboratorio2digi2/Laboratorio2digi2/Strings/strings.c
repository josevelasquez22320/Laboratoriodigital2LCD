/*
 * strings.c
 *
 * Created: 3/02/2025 10:32:12
 *  Author: josea
 */ 
#include "strings.h"

void float_to_string(float num, char *buffer, int precision) {
	// Extract the integer part
	int integer_part = (int)num;
	
	// Get the decimal part by subtracting the integer part
	float decimal_part = num - integer_part;
	
	// Convert the integer part to a string
	char int_buffer[16]; // Temporary buffer for the integer
	snprintf(int_buffer, sizeof(int_buffer), "%d", integer_part);
	
	// Convert the decimal part to a string
	char dec_buffer[16]; // Temporary buffer for the decimal
	for (int i = 0; i < precision; i++) {
		decimal_part *= 10;
	}
	snprintf(dec_buffer, sizeof(dec_buffer), "%d", (int)decimal_part);
	
	// Merge both parts into the final buffer
	snprintf(buffer, 32, "%s.%s", int_buffer, dec_buffer);
}



