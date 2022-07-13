/*
 * File:   IO.c
 * Author: Nathan
 *
 * Created on October 23, 2021, 5:53 PM
 */

#include "xc.h"
#include "timers.h"
#include "gpio.h"
#include "StopWatch.h"

int PBstate = 0b000;
int Mode = 1; //default mode - countdown
extern int min; //minutes
extern int sec; //seconds
extern int hsec; //hundredth of a second
extern int pressedTime; //how long button has been pressed in seconds
extern int countStop; //countdown stop flag
extern int timerStop; //timer stop flag
extern int gameStop; //reaction game stop flag
extern int alarm; //alarm flag
extern char str[30];
extern int PB1; //PB1 from gpio.c
extern int PB2; //PB2 from gpio.c
extern int PB3; //PB3 from gpio.c

void IOinit() {
    TRISAbits.TRISA2 = 1; // Set RA2 as input (B1)
    TRISAbits.TRISA4 = 1; // Set RA4 as input (B2)
    TRISBbits.TRISB4 = 1; // Set RB4 as input (B3)
    TRISBbits.TRISB8 = 0; // Set RB8 as output (LED)

    CNPU2bits.CN30PUE = 1; // RA2 Pull up
    CNPU1bits.CN0PUE = 1; // RA4 Pull up
    CNPU1bits.CN1PUE = 1; // RB4 Pull up

    AD1PCFG = 0xFFFF;
}

void IOCheck() {
    //PB1 : RA2
    //PB2 : RA4
    //PB3 : RB4

    //Check if any pushbuttons are pressed
    if (PB1 == 1 || PB2 == 1 || PB3 == 1) {
        NewClk(8); //Set clock to 8MHz (Speed up clock after input is registered) 
    }

    PBstate = 0b000;

    if (PB1 == 1) {
        PBstate += 0b001;
    }
    if (PB2 == 1) {
        PBstate += 0b010;
    }
    if (PB3 == 1) {
        PBstate += 0b100;
    }

    switch (PBstate) {
        case 0b001: //PB1 pressed
            switch (Mode) {
                case 1: //countdown - adjust minutes
                    if (alarm == 1) {
                        alarm = 0;
                        countStop = 0;
                    }
                    if (min < 59) {
                        min = min + 1;
                        Delay_ms(200);
                    }
                    sprintf(str, "  %02dm : %02ds         ", min, sec);
                    Disp2String(str);
                    XmitUART2('\r', 1);
                    break;
                case 2: //timer - start stop
                    Delay_ms(300);
                    if (timerStop == 0) {
                        Timer();
                    } else if (timerStop == 1) {
                        timerStop = 0;
                        sprintf(str, "  %02dm : %02d.%02ds      ", min, sec, hsec);
                        Disp2String(str);
                        XmitUART2('\r', 1);
                    }
                    break;
            }
            break;
        case 0b010: //PB2 pressed
            switch (Mode) {
                case 1: //countdown - adjust seconds
                    if (alarm == 1) {
                        alarm = 0;
                        countStop = 0;
                    }
                    if (sec < 59) {
                        sec = sec + 1;
                        Delay_ms(200);
                    }
                    sprintf(str, "  %02dm : %02ds         ", min, sec);
                    Disp2String(str);
                    XmitUART2('\r', 1);
                    break;
                case 2: //timer - reset
                    timerStop = 0;
                    min = 0;
                    sec = 0;
                    hsec = 0;
                    sprintf(str, "  %02dm : %02d.%02ds      ", min, sec, hsec);
                    Disp2String(str);
                    XmitUART2('\r', 1);
                    break;
            }
            break;
        case 0b100: //PB3 pressed
            switch (Mode) {
                case 1: //countdown - PB3 long or short press
                    while (PB3 == 1) {
                        sprintf(str, "  %02dm : %02ds  %ds", min, sec, pressedTime);
                        Disp2String(str);
                        XmitUART2('\r', 1);
                        pressedTime = pressedTime + 1;
                        Delay_ms(1000); 
                    }
                    if (pressedTime <= 3) //countdown - start stop
                    {
                        pressedTime = 0;
                        if (min == 0 && sec == 0) {
                            countStop = 1;
                        }
                        if (countStop == 0) {
                            Countdown();
                        } else if (countStop == 1) {
                            countStop = 0;
                            sprintf(str, "  %02dm : %02ds         ", min, sec);
                            Disp2String(str);
                            XmitUART2('\r', 1);
                        }
                    }
                    if (pressedTime > 3) //countdown - reset
                    {
                        pressedTime = 0;
                        alarm = 0;
                        countStop = 0;
                        min = 0;
                        sec = 0;
                        sprintf(str, "  %02dm : %02ds         ", min, sec);
                        Disp2String(str);
                        XmitUART2('\r', 1);
                    }
                    break;
                case 2: //timer - reaction game
                    if (gameStop == 0) {
                        ReactionGame();
                    } else if (gameStop == 1) {
                        gameStop = 0;
                        sprintf(str, "  %02dm : %02d.%02ds      ", min, sec, hsec);
                        Disp2String(str);
                        XmitUART2('\r', 1);
                    }
                    break;
            }
            break;
        case 0b011: //PB1 & PB2 pressed
            while (PB1 == 1 && PB2 == 1) {
                Disp2String("\r Switching modes");
                sprintf(str, " %ds ", pressedTime);
                Disp2String(str);
                XmitUART2('\r', 1);
                pressedTime = pressedTime + 1;
                Delay_ms(1000);
            }
            if (pressedTime > 3) //Mode switch
            {
                pressedTime = 0;
                if (Mode == 1) //countdown to timer
                {
                    if (alarm == 1) {
                        alarm = 0;
                        countStop = 0;
                    }
                    Mode = 2;
                    min = 0;
                    sec = 0;
                    hsec = 0;
                    sprintf(str, "  %02dm : %02d.%02ds      ", min, sec, hsec);
                    Disp2String(str);
                    XmitUART2('\r', 1);
                } else if (Mode == 2) //timer to countdown
                {
                    Mode = 1;
                    min = 0;
                    sec = 0;
                    sprintf(str, "  %02dm : %02ds         ", min, sec);
                    Disp2String(str);
                    XmitUART2('\r', 1);
                }
            } else if (pressedTime <= 3) { //cancel mode switch
                pressedTime = 0;
                if (Mode == 1) //countdown
                {
                    sprintf(str, "  %02dm : %02ds         ", min, sec);
                    Disp2String(str);
                    XmitUART2('\r', 1);
                } else if (Mode == 2) //timer
                {
                    sprintf(str, "  %02dm : %02d.%02ds      ", min, sec, hsec);
                    Disp2String(str);
                    XmitUART2('\r', 1);
                }
            }
            break;
        default: //no pushbuttons
            if (alarm == 1) { //LED on when ALARM
                LATBbits.LATB8 = 1;
            } else if (alarm == 0) {
                LATBbits.LATB8 = 0;
            }
            NewClk(32); //Slow down clock when stop watch is not active
            Delay_ms(100);
            break;
    }
}