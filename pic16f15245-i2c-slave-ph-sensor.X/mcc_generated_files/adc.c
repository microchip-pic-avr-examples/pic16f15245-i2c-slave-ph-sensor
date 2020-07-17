/**
  ADC Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc.c

  @Summary
    This is the generated driver implementation file for the ADC driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for ADC.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.0
        Device            :  PIC16F15245
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.20
        MPLAB             :  MPLAB X 5.40
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "adc.h"
#include "device_config.h"

#define ACQ_US_DELAY 5

void (*ADC_InterruptHandler)(void);

void ADC_Initialize(void)
{
    ADCON0 = 0x01;                                                              // GO_nDONE stop; ADON enabled; CHS ANA0;     
    ADCON1 = 0x80;                                                              // ADFM right; ADPREF VDD; ADCS FOSC/2; 
    ADRESL = 0x00;
    ADRESH = 0x00;   
}

adc_result_t ADC_GetConversion(adc_channel_t channel)
{   
    ADCON0bits.CHS = channel;                                                   // select the A/D channel      
    ADCON0bits.ADON = 1;                                                        // Turn on the ADC module    
    __delay_us(ACQ_US_DELAY);                                                   // Acquisition time delay   
    ADCON0bits.GO_nDONE = 1;                                                    // Start the conversion    
    while (ADCON0bits.GO_nDONE)                                                 // Wait for the conversion to finish
    {
    }
    
    return ((adc_result_t)((ADRESH << 8) + ADRESL));                            // Conversion finished, return the result
}

/**
 End of File
*/