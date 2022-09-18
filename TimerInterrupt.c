/*
 * File:   TimerOVerflow Interrupt.c
 * Author:Anokhautomation
 *
 * Created on September 18, 2022, 1:11 PM
 */
#include <xc.h>
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_OFF & LVP_ON & CPD_OFF & WRT_OFF & CP_OFF);// set configuration bit
#define _XTAL_FREQ 20000000// define crystal frequency
unsigned char timer_count=0;//declare a global variable timer_count

void interrupt timer_0()// ISR Function
{
    if(INTCONbits.TMR0IF == 1)//check flag  TIMER0 is equal to 1 in INTCON Register
    {
        timer_count++;// increment the value of timer_count
        INTCONbits.TMR0IF = 0;//clear the TIMER0 interrupt flag
    }
}

void main(void) // main function
{
    INTCONbits.GIE = 1;//Enable the Global Interrupt bit from INTCON register
    INTCONbits.PEIE = 1;//Enable the peripheral Interrupt bit from INTCON register
    INTCONbits.TMR0IE = 1;//Enable the TIMER0 INterrupt bit from INTCON register
    
    OPTION_REG = 0x07;//set Pre-scaler value to 256
    TMR0 = 59;  //set load value  10MS
    TRISB0=0;// set PORTB RB0  as an output.   
    TRISB1=0;// set PORTB RB1 as an output.   
    TRISB2=0;// set PORTB RB2 as an output.   
       
    
    
    while(1)//infinite loop
    {
        PORTBbits.RB2=1;// keep the PORTB RB2 to HIGH 
        if(timer_count == 0)// check condition-if timer_count is equal to 0
            {
            // then 
              PORTBbits.RB0 = 1;//Turn the RB0 HIgh
              PORTBbits.RB1 = 0;//Turn the RB1 LOW
               
            }
        if(timer_count == 100)// check condition-if timer_count is equal to 100(1000 milli second)
        {
            // then 
            PORTBbits.RB0 = 0;//Turn the RB0 LOW
            PORTBbits.RB1 = 1;//Turn the RB1 HIGH
           
        }
        if(timer_count == 200)// check condition-if timer_count is equal to 200(2000 milli second)
        
        {
            timer_count = 0;//set timer_count value to 0
        }
        
    }    
    return;

}