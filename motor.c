#include <avr/io.h>
#include "motor.h"

//LEFT wheels :PB0 (Arduino pin 8) , when set high forward, when set low reverse
//RIGHT wheels:PD7 (Arduino pin 7) , when set high forward, when set low reverse


void MotorsConfig() {
    TCCR0A = (1 << WGM00) | (1 << WGM01)  | (1 << COM0B1) | (1<<COM0A1); // TIMER0 - Fast PWM configuration
    TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler of 64 -- (16000000/(256*64) = 976Hz) - PWM frequency = 976 Hz
    DDRD |= (1<<DDD3) | (1 << DDD5) | (1<<DDD6) | (1<<DDD7) ; // Set PD5 (OC0B) and PD6 (OC0A) as output pins
    DDRB |= (1 << DDB0); 
    PORTD |= (1<<standby_pin); //standby pin HIGH to activate motor driver
}

void SetSpeed (uint8_t PWM){
    OCR0A = PWM; //supply PWM to left wheels - PIN 6 - PD6
    OCR0B = PWM; //supply PWM to right wheels - PIN 5 - PD5
}


void SetWheelDirection(uint8_t left, uint8_t right) {
    if (left) 
        PORTB |= (1 << left_wheels); 
    else 
        PORTB &= ~(1 << left_wheels);

    if (right) 
        PORTD |= (1 << right_wheels);
    else 
        PORTD &= ~(1 << right_wheels);
}

void DriveStraight (){
    SetWheelDirection(1,1);
    SetSpeed(DEFAULT_SPEED);
}

void Reverse(){
    SetWheelDirection(0,0);
    SetSpeed(DEFAULT_SPEED);   
}

void TurnRight(){
    SetWheelDirection(1,0);
    SetSpeed(50);
}

void TurnLeft(){
    SetWheelDirection(0,1);
    SetSpeed(100);
}

void StopVehicle(){
    SetSpeed(0);
}