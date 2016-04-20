// ******************************************************************************************* //
//
// File:         lab3p1.c
// Date:         3-28-2014
// Authors:      Alex Levine
//
// Description: This file initializes the PWM, and remaps pins to allow the robot to go
//      forwards and backwards. It also shuts off the output compare modules 2, 4, and 5 to
//      go into the idle state. The PWM uses timer 3 with a prescalar of 1 and a PR value of 1023.
// ******************************************************************************************* //

#include <xc.h>
//#include <proc/p32x470f5121.h>
#include "pwm.h"


void initPWM(){
    RPD1Rbits.RPD1R = 0b1011; // map OC2 to RD1, input 1
    RPD9Rbits.RPD9R = 0;    //input 2
    RPD3Rbits.RPD3R = 0b1011; // map OC4 to RD3, input 3 
    
    RPD11Rbits.RPD11R = 0;   //input 4
    T3CONbits.TCKPS=0;
    PR3=100;
    TMR3=0;
    T3CONbits.TON=1;
    OC2CONbits.OCTSEL=1;
    OC2CONbits.OCM=6;       // Configure for PWM mode
    OC2RS=0;
    OC2R=0;     // Initialize primary Compare Register
    
    OC4CONbits.OCTSEL=1;
    OC4CONbits.OCM=6;       // Configure for PWM mode
    OC4RS=0;
    OC4R=0;     // Initialize primary Compare Register
    
    OC5CONbits.OCTSEL=1;
    OC5CONbits.OCM=6;       // Configure for PWM mode
    OC5RS=0;
    OC5R=0;     // Initialize primary Compare Register
    
    OC2CONbits.ON=0;
    OC4CONbits.ON=0;
    OC5CONbits.ON=0;

}

void changeForwards() {
    OC2CONbits.ON=0;
    OC4CONbits.ON=0;
    OC5CONbits.ON=0;
    
    RPD1Rbits.RPD1R = 0b1011; // map OC2 to RD1, input 1
    RPD9Rbits.RPD9R = 0;    //input 2
   // RPD3Rbits.RPD3R = 0b1011; // map OC4 to RD3, input 3 
    //RPD11Rbits.RPD11R = 0;   //input 4
    
    OC2CONbits.ON=1;
    OC4CONbits.ON=1;
    OC5CONbits.ON=0;
}

void turnAround() {
    OC2CONbits.ON=0;
    OC4CONbits.ON=0;
    OC5CONbits.ON=0;
    
    RPD1Rbits.RPD1R = 0; // map OC2 to RD1, input 1
    RPD9Rbits.RPD9R = 0b1011;    //input 2
    //RPD3Rbits.RPD3R = 0; // map OC4 to RD3, input 3 
    //RPD11Rbits.RPD11R = 0b1011;   //input 4
    
    OC2CONbits.ON=0;
    OC4CONbits.ON=1;
    OC5CONbits.ON=1;
    
}

void OC_off() {
    OC2CONbits.ON=0;
    OC4CONbits.ON=0;
    OC5CONbits.ON=0;
}

void OC_on() {
    OC2CONbits.ON=1;
    OC4CONbits.ON=1;
}

void accelerator(int L, int R) {
        
    OC5RS = 0;
	OC2RS = 0;
	OC4RS = 0;

	OC2CONbits.ON = 0;
	OC4CONbits.ON = 0;
	OC5CONbits.ON = 0;
        
    int v;

	if (R < 0) {
	
		RPD1Rbits.RPD1R = 0;
		RPD9Rbits.RPD9R = 0b1011;
		
	}
	else {
	
		RPD1Rbits.RPD1R = 0b1011;
		RPD9Rbits.RPD9R = 0;
	
	}
	if (L < 0) {
		
		RPD3Rbits.RPD3R = 0;
		RPD11Rbits.RPD11R = 0b1011;
		
	}
	else {
	
		RPD3Rbits.RPD3R = 0b1011;
		RPD11Rbits.RPD11R = 0;
	
	}
	
    OC2CONbits.ON = 1;
	OC4CONbits.ON = 1;
	OC5CONbits.ON = 1;
	
	OC5RS = 0;
	OC2RS = 0;
	OC4RS = 0;
	
	if (L < 0) {
	
		OC4RS = 0.3*(-1 * L)+70;
		
	}
	else {
		
		if(L == 0) {
			OC4RS = 0;
		}
		else {
			OC4RS =  0.3*L + 70;
		}
	}
	if (R < 0) {
		
		OC5RS = 0.3*(-1 * R)+70;
		
	}
	else {
	
		if(R == 0) {
            OC2RS = 0;
		}
		else {
			OC2RS = 0.3*R+70;
		}
	
	}
    

    
    delayMs(30);
}