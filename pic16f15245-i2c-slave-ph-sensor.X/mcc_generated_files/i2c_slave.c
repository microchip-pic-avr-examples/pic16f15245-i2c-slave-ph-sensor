/**
  Company:
    Microchip Technology Inc.

  File Name:
    i2c_slave.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.78.1
        Device            :  PIC16F15245
        MPLABX            :  5.40
        XC8               :  2.20
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
#include "mcc.h"

uint8_t slaveAddress = 0x30;                                                    // 7-bit slave address
uint8_t index =           0;                                                    // Array pointer
uint8_t temp =            0;                                                    // Temp register
uint8_t regAdd =          1;                                                    // First data byte was actually register address byte 

void I2C_Initialize(void)
{
    SSP1STATbits.SMP = 1;                                                       // Disable slew control for Standard mode
    SSP1CON1bits.SSPM = 0b0110;                                                 // 7-bit slave mode
    SSP1CON2bits.SEN = 1;                                                       // Enable clock stretching
    SSP1CON3bits.SBCDE = 1;                                                     // Enable bus collision interrupts
    SSP1ADD = slaveAddress;                                                     // Load slave address
    SSP1CON1bits.SSPEN = 1;                                                     // Enable the module
    
    PIR1bits.BCL1IF = 0;                                                        // Clear Bus Collision interrupt flag
    PIR1bits.SSP1IF = 0;                                                        // Clear the SSP interrupt flag
    PIE1bits.BCL1IE = 1;                                                        // Enable BCLIF
    PIE1bits.SSP1IE = 1;                                                        // Enable SSPIF
    INTCONbits.PEIE = 1;                                                        // Enable peripheral interrupts
    INTCONbits.GIE = 1;                                                         // Enable global interrupts
}

void __interrupt() ISR(void)
{
    if(PIR1bits.SSP1IF)                                                         // Check for SSPIF
    {
        if(SSP1STATbits.R_nW == 1)                                              // Master wants to read (slave transmit)
        {
            SSP1BUF = i2cArray[index++];                                        // Load array value
            SSP1CON1bits.CKP = 1;                                               // Release clock stretch                                                          
        }   
        if(SSP1STATbits.R_nW == 0)                                              // Master wants to write (slave receive)
        {
            if(SSP1STATbits.D_nA == 0)                                          // Last byte was an address
            {
                regAdd = 1;                                                     // Next byte will be register address
                temp = SSP1BUF;                                                 // Clear BF
                SSP1CON1bits.CKP = 1;                                           // Release clock stretch
            }
            if(SSP1STATbits.D_nA == 1)                                          // Last byte was data
            {
                if(regAdd == 1)                                                 // If last byte was the register address
                {
                    index = SSP1BUF;                                            // Load register address into index
                    regAdd = 0;                                                 // Next byte will be true data
                }
                else
                {
                    if(index < ARRAY_CNT)                                       // Within array boundaries?
                    {
                        i2cArray[index++] = SSP1BUF;                            // Yes, load data from SSP1BUF
                    }
                    else
                    {
                        temp = SSP1BUF;                                         // No, array location invalid, discard data
                    }
                }
                SSP1CON1bits.CKP = 1;                                           // Release clock stretch
            }
        }
    }
    if(PIR1bits.BCL1IF == 1)
    {
        temp = SSP1BUF;                                                         // Clear BF
        PIR1bits.BCL1IF = 0;                                                    // Clear BCLIF
        SSP1CON1bits.CKP = 1;                                                   // Release clock stretching
    }
    PIR1bits.SSP1IF = 0;                                                        // Clear SSP1IF
}