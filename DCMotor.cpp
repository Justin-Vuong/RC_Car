#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

//define the pin connected to L293D
#define motorPin1    2        
#define motorPin2    0
#define enablePin    3

void dcMotorInit(){
    pinMode(enablePin,OUTPUT);//set mode for the pin
    pinMode(motorPin1,OUTPUT);
    pinMode(motorPin2,OUTPUT);
    softPwmCreate(enablePin,0,100);//define PWM pin
}

void dcMotorWrite(int dir, int power){
	//dir 0 means forward, 1 means backwards
	//power is the PWM Duty Cycle
    if (power == 0) {
        digitalWrite(motorPin1,LOW); 
        digitalWrite(motorPin2,LOW);
        printf("Motor Stop...\n");
    }
    if(dir==0){
        digitalWrite(motorPin1,HIGH);
        digitalWrite(motorPin2,LOW);
        printf("turn Forward...\n");
    } else {
        digitalWrite(motorPin1,LOW);
        digitalWrite(motorPin2,HIGH);
        printf("turn Back...\n");
    }
    
    softPwmWrite(enablePin,power);
    printf("The PWM duty cycle is %d%%\n",power);//print the PMW duty cycle
}
