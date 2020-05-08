#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <linux/joystick.h>
#include <StepperMotor.cpp>
#include <DCMotor.cpp>

int main(void){
    printf("Program is starting ... \n");

    //Init for Joystick
   	int fd = open ("/dev/input/js0", O_RDONLY);
	if (fd < 0){
       printf("No Joystick Detected");
       return -1;
    }
    printf("Opened /dev/input/js0");
	struct js_event e;
	
    wiringPiSetup();

    //Init for DC Motor
    int adjVal = 0; //Value adjusted for PWM Duty Cycle
	bool dcDir = 0; //dcDir = 1 is backwards, 0 is forwards
    dcMotorInit();
    
    //Init for Stepper Motor
    int stepperVal = 0; //stepperVal must always be from -100 to 100 to accomodate limitations of steering mechanism
    bool stepperDir = 0; //stepperDir = 1 is CCW, 0 = CW
    stepperInit();
    
    while(1){
        read (fd, &e, sizeof(e));
        if (e.number == 0){

            if (e.value < 0 && stepperVal >= -90){
                stepperDir = 1;
                stepperVal -= 10;
                printf("\nLeft: %d",stepperVal);
                moveOnePeriod(stepperDir, 3);
            } else if (stepperVal <= 90) {
                stepperDir = 0;
                stepperVal += 10;
                printf("\nRight: %d",stepperVal);
                moveOnePeriod(stepperDir, 3);
            }
        } else if (e.number == 1){
            if (e.value < 0){
                adjVal = (e.value / -327.67);
                dcDir = 0;
                printf("\nUp: %d",adjVal);
            } else {
                adjVal = (e.value / 327.67);
                dcDir = 1;
                printf("\nDown: %d",adjVal);
            }
            dcMotorWrite(dcDir, adjVal);
        }
        
        
        delay(100);
    }
    return 0;
}

