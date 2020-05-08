#include <stdio.h>
#include <wiringPi.h>

const int motorPins[]={1,4,5,6};    //define pins connected to four phase ABCD of stepper motor 
const int CCWStep[]={0x01,0x02,0x04,0x08};  //define power supply order for coil for rotating anticlockwise 
const int CWStep[]={0x08,0x04,0x02,0x01};   //define power supply order for coil for rotating clockwise
//as for four phase stepping motor, four steps is a cycle. the function is used to drive the stepping motor clockwise or anticlockwise to take four steps

void stepperInit(){
    for(int i=0;i<4;i++){
        pinMode(motorPins[i],OUTPUT);
    }
}

void moveOnePeriod(int dir,int ms){
    
    for (int steps = 0; steps < 10; steps++){
        for (int j=0;j<4;j++){  //cycle according to power supply order 
            for (int i=0;i<4;i++){  //assign to each pin, a total of 4 pins
                if(dir == 1)    //power supply order clockwise
                    digitalWrite(motorPins[i],(CCWStep[j] == (1<<i)) ? HIGH : LOW);
                else        //power supply order anticlockwise
                    digitalWrite(motorPins[i],(CWStep[j] == (1<<i)) ? HIGH : LOW);
                //printf("motorPin %d, %d \n",motorPins[i],digitalRead(motorPins[i]));
            }
            //printf("Step cycle!\n");
            if(ms<3)        //the delay can not be less than 3ms, otherwise it will exceed speed limit of the motor
                ms=3;
            delay(ms);
        }
    }
}

