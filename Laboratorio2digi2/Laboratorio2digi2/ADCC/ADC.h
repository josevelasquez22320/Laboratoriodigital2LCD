/*
 * ADC.h
 *
 * Created: 2/02/2025 10:53:57
 *  Author: josea
 */ 


#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
#include <stdint.h>

// Initializes the ADC module with predefined settings.
void initADC(void);

// Converts an analog signal from the specified channel to a digital value.
// Parameters:
// - canal: ADC channel number to read from.
// Returns:
// - 10-bit digital value representing the analog input.
uint16_t ADC_CONVERT(uint8_t canal);




#endif /* ADC_H_ */