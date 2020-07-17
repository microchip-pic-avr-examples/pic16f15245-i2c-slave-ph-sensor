/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.0
        Device            :  PIC16F15245
        Driver Version    :  2.00
        IDE version       :  5.40
        XC8 Compiler      :  2.20
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

#include "mcc_generated_files/mcc.h"

uint16_t pHSensor = 0;
float pHVoltage = 0.00;
float pHValue = 0.00;
uint24_t pHCopy = 0;
uint24_t newpH = 0;
uint8_t pHLowByte = 0;
uint16_t pHHighByte = 0;
uint24_t pHUpperByte = 0;
#define MAX_ADC  1023.00
#define PH_SLOPE -5.6548
#define PH_OFFSET 15.509

void main(void)
{
    SYSTEM_Initialize();
    __delay_ms(4000);                                                           // Delay for pH sensor
    while (1)
    {
        pHSensor = ADC_GetConversion(channel_ANA2);                             // Read pH sensor
        pHVoltage = (pHSensor/MAX_ADC);                                         // Convert into voltage
        pHVoltage = pHVoltage * 5;
        pHValue = (PH_SLOPE * pHVoltage);                                       // Convert to pH value
        pHValue = pHValue + PH_OFFSET;
        //printf("pH Value = %1.1f \r\n", pHValue);                               // Print value for testing

 //Uncomment these lines when ready to use as an I2C Slave         
        (uint24_t)pHCopy = (float)pHValue * 100;       
        // Break down the float variable into 3 bytes to transmit over I2C
        pHLowByte = pHCopy & 0xFF;                                              // Get low byte
        pHHighByte = (pHCopy >> 8) & 0xFF;                                      // Get high byte
        pHUpperByte = (pHCopy >> 16) & 0xFF;                                    // Get upper byte
        (uint8_t)i2cArray[0] = (uint8_t)pHLowByte;
        (uint8_t)i2cArray[1] = (uint16_t)pHHighByte;
        (uint8_t)i2cArray[2] = (uint24_t)pHUpperByte;

        
/*The lines below can be used to ensure the I2C transmitted value is correct when rebuilt by master software                                
        (uint24_t)newpH = ((uint24_t)i2cArray[2] << 16);
        (uint24_t)newpH = (uint24_t)newpH + ((uint16_t)i2cArray[1] << 8);
        (uint24_t)newpH = (uint24_t)newpH + i2cArray[0];
        
        (float)pHValue = (uint24_t)newpH;
        pHValue /= 100.00;
        printf("pH Value = %1.1f \r\n", pHValue);
*/   
        __delay_ms(1000);
    }
}
/**
 End of File
*/