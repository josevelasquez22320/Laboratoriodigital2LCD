/*
 * strings.h
 *
 * Created: 3/02/2025 10:31:57
 *  Author: josea
 */ 


#ifndef STRINGS_H_
#define STRINGS_H_
#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Converts a floating-point number to a string with the specified precision.
// - precision: Number of decimal places to include in the output string.
void float_to_string(float num, char *buffer, int precision);

#endif /* STRINGS_H_ */