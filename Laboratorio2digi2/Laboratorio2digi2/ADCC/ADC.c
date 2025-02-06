/*
 * ADC.c
 *
 * Created: 30/01/2025 10:54:08
 *  Author: josea
 */ 
#include "ADC.h"

void initADC(void){
	ADMUX = 0;
	//Vref = AVcc = 5Vs
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);
	
	ADMUX |= (1 << ADLAR);
	
	ADCSRA = 0;
	ADCSRA |= (1 << ADEN);	//on ADC
	ADCSRA |= (1 << ADIE);	//int
	
	//pres 128 > 125kHz
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	DIDR0 |= (1 << ADC0D) | (1 << ADC1D) | (1 << ADC2D);	//PC0 desabilita
}
