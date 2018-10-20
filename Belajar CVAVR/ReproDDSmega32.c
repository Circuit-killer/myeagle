/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
� Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 9/13/2013
Author  : 
Company : 
Comments: 


Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*****************************************************/

#include <mega32.h>

// Alphanumeric LCD Module functions

// Declare your global variables here
#include <delay.h>
#include <stdint.h>

#define DAT_2   PORTB.0
#define CLK     PORTB.1         
#define FUD     PORTB.2         
#define DAT     PORTB.3         
#define RST     PORTB.4

#define LOW     0
#define HIGH    1

eeprom uint32_t freq = 1000000;
//eeprom uint32_t d_freq;
//eeprom uint32_t step = 1000000;
//eeprom uint32_t d_step;

void dds_reset(void)
{
        CLK = LOW;
        FUD = LOW;
        DAT = LOW;
        
        RST = LOW;      delay_us(5);
        RST = HIGH;     delay_us(5);
        RST = LOW;
        
        CLK = LOW;      delay_us(5);
        CLK = HIGH;     delay_us(5);
        CLK = LOW;
        
        FUD = LOW;      delay_us(5);
        FUD = HIGH;     delay_us(5);
        FUD = LOW; 
}

void send_data(void)
{
        uint32_t data_word = (freq * 4294967296) / 100000000; 
        int i; 
        
        FUD = HIGH;     delay_us(5); 
        FUD = LOW;
        
        for(i=0; i<40; i++)
        {
                DAT = ((data_word >> i) & 0x01);  
                delay_us(10);
                   
                CLK = HIGH;     
                delay_us(5);
                CLK = LOW;
        }      
            
        delay_us(10);
        
        FUD = HIGH;     
        delay_us(5); 
        FUD = LOW;
}

void main(void)
{
        PORTA=0xFF;
        DDRA=0x00;
        PORTB=0x00;
        DDRB=0xFF;
        PORTC=0xFF;
        DDRC=0x00;
        PORTD=0x00;
        DDRD=0xFF; 
        
        ACSR=0x80;
        SFIOR=0x00;

        dds_reset();
        send_data();

        while (1)
        {
            //tuning();
        }
}
