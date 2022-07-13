/*
 * File:   StopWatch.c
 * Author: Justin
 *
 * Created on November 19, 2021, 3:45 PM
 */


#include "xc.h"
#include "timers.h"
#include "gpio.h"

int min = 0; //minutes
int sec = 0; //seconds
int hsec = 0; //hundredth of a second
int pressedTime = 0; //how long button has been pressed in seconds
int countStop = 0; //countdown stop flag
int timerStop = 0; //timer stop flag
int gameStop = 0; //reaction game stop flag
int alarm = 0; //alarm flag
char str[30];
extern int PB1; //PB1 from gpio.c
extern int PB2; //PB2 from gpio.c
extern int PB3; //PB3 from gpio.c

void Countdown() {
    int blink = 0;

    while (countStop == 0) {
        if (sec >= 0) {
            sec = sec - 1; //countdown seconds
            if (blink == 0) { //1 sec blink rate
                blink = 1;
                LATBbits.LATB8 = 1;
                Delay_ms(1000);
            } else if (blink == 1) {
                blink = 0;
                LATBbits.LATB8 = 0;
                Delay_ms(1000);
            }
            if (sec < 0) {
                min = min - 1; //countdown minutes
                sec = 59;
            }
            if (PB3 == 1) { //countdown stop flag
                countStop = 1;
                min = min;
                sec = sec + 1;
            }
            sprintf(str, "  %02dm : %02ds         ", min, sec);
            Disp2String(str);
            if (min == 0 && sec == 0) { //ALARM
                XmitUART2('\r', 1);
                sprintf(str, "  %02dm : %02ds -- ALARM", min, sec);
                Disp2String(str);
                alarm = 1;
                countStop = 1;
                LATBbits.LATB8 = 1;
            }
            XmitUART2('\r', 1);
        }
    }
}

void Timer() {
    while (timerStop == 0) {
        LATBbits.LATB8 = 1;

        hsec = hsec + 1; //increment hsec twice to account for display delays
        Delay_ms(1);
        if (PB1 == 1) { //timer stop flag - check on first increment
            timerStop = 1;
            min = min;
            sec = sec;
            hsec = hsec;
            LATBbits.LATB8 = 0;
            break;
        }
        hsec = hsec + 1;
        Delay_ms(1);
        if (PB1 == 1) { //timer stop flag - check on second increment
            timerStop = 1;
            min = min;
            sec = sec;
            hsec = hsec;
            LATBbits.LATB8 = 0;
            break;
        }
        if (hsec > 99) {
            hsec = 0;
            sec = sec + 1; //increment seconds
            if (sec > 59) {
                sec = 0;
                min = min + 1; //increment minutes
            }
        }
        if (PB2 == 1) { //timer reset flag
            timerStop = 1;
            min = 0;
            sec = 0;
            hsec = 0;
        }
        sprintf(str, "  %02dm : %02d.%02ds", min, sec, hsec);
        Disp2String(str);
        XmitUART2('\r', 1);
    }
}

void ReactionGame() {
    int ReadySetGo = 0;

    while (gameStop == 0) {
        if (PB2 == 1) { //game exit flag
            gameStop = 1;
            min = 0;
            sec = 0;
            hsec = 0;
        }
        if (PB3 == 1) { //game reset flag
            ReadySetGo = 0;
            min = 0;
            sec = 0;
            hsec = 0;
            sprintf(str, "  %02dm : %02d.%02ds      ", min, sec, hsec);
            Disp2String(str);
            XmitUART2('\r', 1);
        }
        if (ReadySetGo == 0) { //wait period
            Delay_ms(1000); //1 sec blink rate
            LATBbits.LATB8 = 1;
            Delay_ms(1000);
            LATBbits.LATB8 = 0;
            Delay_ms(1000);
            LATBbits.LATB8 = 1;
            Delay_ms(1000);
            LATBbits.LATB8 = 0;
            Delay_ms(1000);
            LATBbits.LATB8 = 1;
            Delay_ms(1000);
            LATBbits.LATB8 = 0;

            ReadySetGo = 1;
        }
        while (ReadySetGo == 1) { //game start
            srand(time(0));
            int r = (rand() % 2500) + 500; //random number between 500-3000
            Delay_ms(r);
            LATBbits.LATB8 = 1;
            Timer();
            timerStop = 0;
            ReadySetGo = 2;
        }
    }
}