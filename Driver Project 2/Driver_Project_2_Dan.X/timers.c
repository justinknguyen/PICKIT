/*
 * File:   config.c
 * Author: dan.tran2
 *
 * Created on October 15, 2021, 7:39 PM
 */


#include "xc.h"

void Delay_ms(uint16_t time_ms)
{
    // Clear TMR2
    TMR2 = 0;
    
    // Configure T2CON register bits
    T2CONbits.TCS = 0;      //Select internal clock (Fosc/2)
    T2CONbits.T32 = 0;      //Keep timer 2 as discrete 16-bit timer
    T2CONbits.TCKPS1 = 1;   
    T2CONbits.TCKPS0 = 1;   // ^Pre-scaler 1:256
    T2CONbits.TSIDL = 0;    //Continue module operation in idle mode
    T2CONbits.TON = 1;      //Starts 16-bit timer 2
    
    // Set timer2 interrupt priority to 6
    IPC1bits.T2IP2 = 1;
    IPC1bits.T2IP1 = 1;
    IPC1bits.T2IP0 = 0;
    
    // Enable timer2 interrupt
    IEC0bits.T2IE = 1;
    
    // Clear timer2 interrupt flag
    IFS0bits.T2IF = 0;
    
    // Compute PR2 with 8 MHz
    PR2 = time_ms*15;
    
    Idle();
}

void __attribute__((interrupt,no_auto_psv)) _T2Interrupt(void)
{
    IFS0bits.T2IF = 0;  //clear timer 2 interrupt flag
    T2CONbits.TON = 0;  //stop timer
}

