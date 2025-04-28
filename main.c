
#include "motor.h"
#include "ultrasonic.h"
#include "EspData.h"
#include"servo.h"
#include "LineFollowing.h"

#include <util/delay.h>

extern volatile int state;//from EspData.c 
extern volatile int count;//from LineFollowing.c
volatile float distance = 0;
volatile int previous_state = 0;

void NextStation(){
    if (count>=1){
        state = 0;
        _delay_ms(100);
        count = 0;
        }
}

void checkDistance(){
    if (distance > 2.0 && distance < 10.0){
        StopVehicle();
    }
}

void checkState(){
    if (previous_state == 0)
        state = 0;
    else if (previous_state == 1)
        state = 1; 
}

int main (){
    initUART(9600);
    MotorsConfig();
    sei();// Enable global interrupts
    ADC_init();
    Timer1_Init();
    ServoConfig();

    while(1){
                
        if (state==1){                            //Next Station
            if (previous_state == 0) {
                DriveStraight();
                _delay_ms(500);
                count = 0;
            }   
            distance = GetUltrasonicDistance();
            _delay_ms(10);
            LineFollowing(); 
            checkDistance();
            NextStation();
            previous_state = 1; 
        }
        else if (state==2){                        //ServoCounterClockwise
            LoadLeft();
        }
        else if (state==3){                         //ServoClockwise
            LoadRight();
        }
        else if (state==4){                         //ServoCentre
            DoneLoading();
        }
        else if (state==0){                         //Stop
            StopVehicle();
            previous_state = 0;
        } 
    }   
}

