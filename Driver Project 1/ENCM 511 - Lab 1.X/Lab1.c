/*
 * File:   Lab1.c
 * Author: Justin Nguyen - 30042258
 *
 * Created on September 29, 2021, 11:15 AM
 */


#include "xc.h"

int main(void) {
    TRISAbits.TRISA0 = 1; //Sets RA0-GPIO2 as input
    TRISAbits.TRISA1 = 1; //Sets RA1-GPIO3 as input
    TRISAbits.TRISA2 = 1; //Sets RA2-GPIO7 as input
    TRISAbits.TRISA4 = 1; //Sets RA4-GPIO10 as input

    TRISBbits.TRISB0 = 0; //Sets RB0-GPIO4 as output
    TRISBbits.TRISB1 = 0; //Sets RB1-GPIO5 as output
    TRISBbits.TRISB2 = 0; //Sets RB2-GPIO6 as output
    TRISBbits.TRISB4 = 0; //Sets RB4-GPIO9 as output
    TRISBbits.TRISB7 = 0; //Sets RB7-GPIO11 as output
    TRISBbits.TRISB8 = 0; //Sets RB8-GPIO12 as output
    TRISBbits.TRISB9 = 0; //Sets RB9-GPIO13 as output
    TRISBbits.TRISB12 = 0; //Sets RB12-GPIO15 as output
   
    
    while(1) //
    {
        if(PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA4 == 0) 
            //input = 0000
        {
            //LEDs, output = 0
            LATBbits.LATB0 = 0; //low
            LATBbits.LATB1 = 0; //low 
            LATBbits.LATB2 = 0; //low
            LATBbits.LATB4 = 0; //low
            LATBbits.LATB7 = 0; //low
            LATBbits.LATB8 = 0; //low
            LATBbits.LATB9 = 0; //low
            LATBbits.LATB12 = 0; //low
        }
        else if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA4 == 0) 
            //input = 0001
        {
            //LEDs, output = 3
            LATBbits.LATB0 = 1; //high
            LATBbits.LATB1 = 1; //high
            LATBbits.LATB2 = 1; //high
            LATBbits.LATB4 = 0; //low
            LATBbits.LATB7 = 0; //low
            LATBbits.LATB8 = 0; //low
            LATBbits.LATB9 = 0; //low
            LATBbits.LATB12 = 0; //low
        }
        else if(PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA2 == 0 && PORTAbits.RA4 == 0) 
            //input = 0010
        {
            //LEDs, output = 0
            LATBbits.LATB0 = 0; //low
            LATBbits.LATB1 = 0; //low 
            LATBbits.LATB2 = 0; //low
            LATBbits.LATB4 = 0; //low
            LATBbits.LATB7 = 0; //low
            LATBbits.LATB8 = 0; //low
            LATBbits.LATB9 = 0; //low
            LATBbits.LATB12 = 0; //low
        }
        else if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 1 && PORTAbits.RA2 == 0 && PORTAbits.RA4 == 0) 
            //input = 0011
        {
            //LEDs, output = 0
            LATBbits.LATB0 = 0; //low
            LATBbits.LATB1 = 0; //low 
            LATBbits.LATB2 = 0; //low
            LATBbits.LATB4 = 0; //low
            LATBbits.LATB7 = 0; //low
            LATBbits.LATB8 = 0; //low
            LATBbits.LATB9 = 0; //low
            LATBbits.LATB12 = 0; //low
        }
        else if(PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 1 && PORTAbits.RA4 == 0)
            //input = 0100
        {
            //LEDs, output = 4
            LATBbits.LATB0 = 1; //high
            LATBbits.LATB1 = 1; //high
            LATBbits.LATB2 = 1; //high
            LATBbits.LATB4 = 1; //high
            LATBbits.LATB7 = 0; //low
            LATBbits.LATB8 = 0; //low
            LATBbits.LATB9 = 0; //low
            LATBbits.LATB12 = 0; //low
        }
        else if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 1 && PORTAbits.RA4 == 0)
            //input = 0101
        {
            //LEDs, output = 2
            LATBbits.LATB0 = 1; //high
            LATBbits.LATB1 = 1; //high
            LATBbits.LATB2 = 0; //low
            LATBbits.LATB4 = 0; //low
            LATBbits.LATB7 = 0; //low
            LATBbits.LATB8 = 0; //low
            LATBbits.LATB9 = 0; //low
            LATBbits.LATB12 = 0; //low
        }
        else if(PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA2 == 1 && PORTAbits.RA4 == 0)
            //input = 0110
        {
            //LEDs, output = 2
            LATBbits.LATB0 = 1; //high
            LATBbits.LATB1 = 1; //high
            LATBbits.LATB2 = 0; //low
            LATBbits.LATB4 = 0; //low
            LATBbits.LATB7 = 0; //low
            LATBbits.LATB8 = 0; //low
            LATBbits.LATB9 = 0; //low
            LATBbits.LATB12 = 0; //low
        }
        else if(PORTAbits.RA0 == 1 && PORTAbits.RA1 == 1 && PORTAbits.RA2 == 1 && PORTAbits.RA4 == 0)
            //input = 0111
        {
            //LEDs, output = 5
            LATBbits.LATB0 = 1; //high
            LATBbits.LATB1 = 1; //high
            LATBbits.LATB2 = 1; //high
            LATBbits.LATB4 = 1; //high
            LATBbits.LATB7 = 1; //high
            LATBbits.LATB8 = 0; //low
            LATBbits.LATB9 = 0; //low
            LATBbits.LATB12 = 0; //low
        }
        else if(PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA4 == 1)
            //input = 1000
        {
            //LEDs, output = 8
            LATBbits.LATB0 = 1; //high
            LATBbits.LATB1 = 1; //high
            LATBbits.LATB2 = 1; //high
            LATBbits.LATB4 = 1; //high
            LATBbits.LATB7 = 1; //high
            LATBbits.LATB8 = 1; //high
            LATBbits.LATB9 = 1; //high
            LATBbits.LATB12 = 1; //high
        }
        else
            //input 1001-1111
        {
            //LEDs, output = 0
            LATBbits.LATB0 = 0; //low
            LATBbits.LATB1 = 0; //low 
            LATBbits.LATB2 = 0; //low
            LATBbits.LATB4 = 0; //low
            LATBbits.LATB7 = 0; //low
            LATBbits.LATB8 = 0; //low
            LATBbits.LATB9 = 0; //low
            LATBbits.LATB12 = 0; //low
        }                    
    }
    return;
}
