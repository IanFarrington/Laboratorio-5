#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "pwm_lib.h"

#define MIN_PULSO 1000.0
#define MAX_PULSO 5000.0
#define MUESTRAS 50

void ADC_init() {
	ADMUX = (1 << REFS0); // AVcc como referencia
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128
}

uint16_t ADC_leer(uint8_t canal) {
	ADMUX = (ADMUX & 0xF8) | (canal & 0x07);
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	return ADC;
}

int main() {
	PWM_init();
	ADC_init();

	while(1) {
		uint16_t valor_adc = ADC_leer(0);
		uint16_t ancho_pulso = (valor_adc * ((MAX_PULSO - MIN_PULSO) / 1023.0)) + MIN_PULSO;
		PWM_set_duty_us(ancho_pulso);
	}
}
