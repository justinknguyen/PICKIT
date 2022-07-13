/*
 * File:   Voltage.c
 * Author: Dan Tran
 *
 * Created on November 24, 2021, 5:00 PM
 */


#include "xc.h"

void VoltageCheck()
{
    uint32_t VoltageAverage = 0;
    uint32_t ADCvalue1 = 0;
    int i;
    for (i = 0; i < 10; i++)
    {
        uint32_t VoltageAverage1000 = 0;
        int j;
        for (j = 0; j < 1000; j++)
        {
            uint16_t ADCvalue = ADC();
            ADCvalue1 = ADCvalue;
            VoltageAverage1000 += ADCvalue;
            Delay_us(600);
        }
        VoltageAverage += VoltageAverage1000/1000;
    }
    
    BarGraph(VoltageAverage/10);
    //BarGraph(ADCvalue1);
}
