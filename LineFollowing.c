#include <avr/io.h>
#include "LineFollowing.h"
#include "motor.h"


#define RIGHT_SENSOR_CH  0
#define MIDDLE_SENSOR_CH 1
#define LEFT_SENSOR_CH   2


volatile uint16_t leftSensorValue = 0;
volatile uint16_t middleSensorValue = 0;
volatile uint16_t rightSensorValue = 0;
volatile int count = 0;


void ADC_init(){
    ADCSRA |= (1 << ADEN); //enable ADC
    ADMUX |= (1 << REFS0); // Vref connect internally to AVcc
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);//Set prescale to 128 (16000000/128 = 125Khz) -- 10-bit resolution
}

uint16_t ADC_read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | channel; // Set the ADC channel
    ADCSRA |= (1 << ADSC); // Start conversion
    while (ADCSRA & (1 << ADSC)); // Wait until conversion completes
    return ADC; // Return the ADC value
}


void LineFollowing(){
    uint16_t threshold  = 200;
    leftSensorValue = ADC_read(LEFT_SENSOR_CH);  
    middleSensorValue = ADC_read(MIDDLE_SENSOR_CH);  
    rightSensorValue = ADC_read(RIGHT_SENSOR_CH);  
    DriveStraight();
    if (leftSensorValue < threshold){
        TurnLeft();
        if (leftSensorValue > threshold)
            DriveStraight();
    }
    
    if (rightSensorValue < threshold){
        TurnRight();
        if (rightSensorValue > threshold)
            DriveStraight();
    }
    
    if (middleSensorValue > 500)
        count++;   

}