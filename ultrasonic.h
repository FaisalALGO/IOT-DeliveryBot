#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include <stdint.h>
#include "motor.h"
#include <avr/interrupt.h>
#define EchoPin PB4
#define TriggerPin PB5

void Timer1_Init();
float  GetUltrasonicDistance();


#endif