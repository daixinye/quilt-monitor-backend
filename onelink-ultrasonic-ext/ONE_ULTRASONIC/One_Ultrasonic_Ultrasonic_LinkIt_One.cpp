
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"
#include "One_Ultrasonic_Ultrasonic_LinkIt_One.h"

#ifdef STM32F4

static uint32_t MicrosDiff(uint32_t begin, uint32_t end)
{
	return end - begin;
}

static uint32_t pulseIn(uint32_t pin, uint32_t state, uint32_t timeout = 1000000L)
{
	uint32_t begin = micros();
	
	// wait for any previous pulse to end
	while (digitalRead(pin)) if (MicrosDiff(begin, micros()) >= timeout) return 0;
	
	// wait for the pulse to start
	while (!digitalRead(pin)) if (MicrosDiff(begin, micros()) >= timeout) return 0;
	uint32_t pulseBegin = micros();
	
	// wait for the pulse to stop
	while (digitalRead(pin)) if (MicrosDiff(begin, micros()) >= timeout) return 0;
	uint32_t pulseEnd = micros();
	
	return MicrosDiff(pulseBegin, pulseEnd);
}

#endif

TL_Ultrasonic::TL_Ultrasonic(int pin)
{
	_pin = pin;
}
/*The measured distance from the range 0 to 400 Centimeters*/
long TL_Ultrasonic::MeasureInCentimeters(void)
{
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	delayMicroseconds(2);
	digitalWrite(_pin, HIGH);
	delayMicroseconds(5);
	digitalWrite(_pin,LOW);
	pinMode(_pin,INPUT);
	long duration;
	duration = pulseIn(_pin,HIGH);
	long RangeInCentimeters;
	RangeInCentimeters = duration/29/2;
	return RangeInCentimeters;
}
/*The measured distance from the range 0 to 157 Inches*/
long TL_Ultrasonic::MeasureInInches(void)
{
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	delayMicroseconds(2);
	digitalWrite(_pin, HIGH);
	delayMicroseconds(5);
	digitalWrite(_pin,LOW);
	pinMode(_pin,INPUT);
	long duration;
	duration = pulseIn(_pin,HIGH);
	long RangeInInches;
	RangeInInches = duration/74/2;
	return RangeInInches;
}
