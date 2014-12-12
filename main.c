#include <msp430.h> 
#include "Maze.h"

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    BCSCTL1 = CALBC1_8MHZ;									// 8MHz clock
    DCOCTL = CALDCO_8MHZ;

    P2DIR |= BIT2;							// P2.2 is associated with TACCTL1
    P2SEL |= BIT2;

    P2DIR |= BIT4;							// P2.4 is associated with TACCTL2
    P2SEL |= BIT4;

    TA1CTL = ID_3 | TASSEL_2 | MC_1;		//set duty cycle and MCLK
    TA1CCR0 = 100;

    TA1CCR1 = 50;
    TA1CCTL1 = OUTMOD_7;					// set TACCTL1 to Reset / Set mode

    TA1CCR2 = 50;						// set TACCTL2 to Set / Reset mode
    TA1CCTL2 = OUTMOD_3;


     ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE;		 // ADC10ON, interrupt enabled
     ADC10CTL1 = ADC10DIV_7;
     ADC10CTL1 |= ADC10SSEL1|ADC10SSEL0;  				// Select SMCLK


     for (;;){
    	 stopMovement();
    	 _delay_cycles(110000);

    	 if(leftSensor() < 0x190)					// two if statements to stay close to left wall
    	 {
    		 	turnLeftLittle();
    			_delay_cycles(9000);
    			stopMovement();
    			_delay_cycles(100000);
    	 }
    	 if(leftSensor() >= 0x170)
    	 {
    		 turnRightLittle();
    		 _delay_cycles(9000);
    		  stopMovement();
   			_delay_cycles(100000);
    	 }
    	 if (centerSensor() >=0x170 && leftSensor() >= 0x165)		// statement to turn right if both left and center sensors triggered
    	 {
    		 turnRightBig();
    		 _delay_cycles(7500);
    		stopMovement();
    		_delay_cycles(100000);
    	 }
    	 if (centerSensor() < 0x170 && leftSensor() >= 0x170)		// has robot move forward when neither sensors are triggered
    	    {
    	      moveForward();
    	      _delay_cycles(100000);
    	    }

    	 else if (centerSensor() < 0x190)
    	 {
    		 moveForward();
    		 _delay_cycles(100000);
    	 }

     }
   return 0;
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
__bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}


unsigned int leftSensor() {				// code for left, right and center sensors using P1.3, P1.4 and P1.5 and the input channels									//
	ADC10CTL0 &= ~ENC;					// that correspond to those pins
	ADC10CTL1 = INCH_3;
	ADC10AE0 |= BIT3;
    ADC10CTL0 |= ENC + ADC10SC;
    __bis_SR_register(CPUOFF + GIE);

    return ADC10MEM;
}

unsigned int rightSensor() {
	ADC10CTL0 &= ~ENC;
	ADC10CTL1 = INCH_4;
	ADC10AE0 |= BIT4;
    ADC10CTL0 |= ENC + ADC10SC;
    __bis_SR_register(CPUOFF + GIE);

    return ADC10MEM;
}

unsigned int centerSensor() {
	ADC10CTL0 &= ~ENC;
	ADC10CTL1 = INCH_5;
	ADC10AE0 |= BIT5;
    ADC10CTL0 |= ENC + ADC10SC;
    __bis_SR_register(CPUOFF + GIE);

    return ADC10MEM;
}

void moveForward() {

    P2DIR |= BIT5;							// Left motor forward
    P2OUT &= ~BIT5;

    P2DIR |= BIT1;							// Right motor forward
    P2OUT &= ~BIT1;
}

void stopMovement(){

    P2DIR |= BIT5;						// Left motor stop forward
    P2OUT |= BIT5;

    P2DIR |= BIT1;						// Right motor stop forward
    P2OUT |= BIT1;

    P2DIR |= BIT0;						// Right motor stop reverse
    P2OUT |= BIT0;

    P2DIR |= BIT3;						// Left motor stop forward
    P2OUT |= BIT3;
}

void turnLeftLittle(){

	P2DIR |= BIT1;							// Right motor forward
	P2OUT &= ~BIT1;
	P2DIR |= BIT3;							// Left motor reverse
	P2OUT &= ~BIT3;
	_delay_cycles(10000000/120);				// implements turn less than 45 degrees
	stopMovement();

}

void turnRightLittle(){

	P2DIR |= BIT5;							// Left motor forward
	P2OUT &= ~BIT5;
	_delay_cycles(10000000/120);				// implements turn less than 45 degrees
    stopMovement();

}

void turnLeftBig(){

	P2DIR |= BIT1;							// Right motor forward
	P2OUT &= ~BIT1;
	P2DIR |= BIT3;							// Left motor reverse
	P2OUT &= ~BIT3;
	_delay_cycles(10000000/15);				// implements turn greater than 45 degrees
   	stopMovement();

}

void turnRightBig(){

	P2DIR |= BIT5;							// Left motor forward
	P2OUT &= ~BIT5;
	P2DIR |= BIT0;							// Right motor reverse
	P2OUT &= ~BIT0;
	_delay_cycles(10000000/10);				// implements turn greater than 45 degrees
   	stopMovement();
}

void moveBackward(){

    P2DIR |= BIT3;							// Left motor reverse
    P2OUT &= ~BIT3;

    P2DIR |= BIT0;							// Right motor reverse
    P2OUT &= ~BIT0;

}
