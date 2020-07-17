/**
  EUSART1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart1.h

  @Summary
    This is the generated header file for the EUSART1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for EUSART1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.0
        Device            :  PIC16F15245
        Driver Version    :  2.1.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.20
        MPLAB 	          :  MPLAB X 5.40
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

#ifndef EUSART1_H
#define EUSART1_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif


#define EUSART1_DataReady  (EUSART1_is_rx_ready())

typedef union {
    struct {
        unsigned perr : 1;
        unsigned ferr : 1;
        unsigned oerr : 1;
        unsigned reserved : 5;
    };
    uint8_t status;
}eusart1_status_t;


/**
  Section: EUSART1 APIs
*/

/**
  @Summary
    Initialization routine that takes inputs from the EUSART1 GUI.

  @Description
    This routine initializes the EUSART1 driver.
    This routine must be called before any other EUSART1 routine is called.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    
*/
void EUSART1_Initialize(void);


/**
  @Summary
    Read a byte of data from the EUSART1.

  @Description
    This routine reads a byte of data from the EUSART1.

  @Preconditions
    EUSART1_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if the receiver is not empty before calling this function.

  @Param
    None

  @Returns
    A data byte received by the driver.
*/
uint8_t EUSART1_Read(void);

 /**
  @Summary
    Writes a byte of data to the EUSART1.

  @Description
    This routine writes a byte of data to the EUSART1.

  @Preconditions
    EUSART1_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if transmitter is not busy before calling this function.

  @Param
    txData  - Data byte to write to the EUSART1

  @Returns
    None
*/
void EUSART1_Write(uint8_t txData);



/**
  @Summary
    Set EUSART1 Framing Error Handler

  @Description
    This API sets the function to be called upon EUSART1 framing error

  @Preconditions
    Initialize  the EUSART1 before calling this API

  @Param
    Address of function to be set as framing error handler

  @Returns
    None
*/
void EUSART1_SetFramingErrorHandler(void (* interruptHandler)(void));

/**
  @Summary
    Set EUSART1 Overrun Error Handler

  @Description
    This API sets the function to be called upon EUSART1 overrun error

  @Preconditions
    Initialize  the EUSART1 module before calling this API

  @Param
    Address of function to be set as overrun error handler

  @Returns
    None
*/
void EUSART1_SetOverrunErrorHandler(void (* interruptHandler)(void));

/**
  @Summary
    Set EUSART1 Error Handler

  @Description
    This API sets the function to be called upon EUSART1 error

  @Preconditions
    Initialize  the EUSART1 module before calling this API

  @Param
    Address of function to be set as error handler

  @Returns
    None
*/
void EUSART1_SetErrorHandler(void (* interruptHandler)(void));



#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // EUSART1_H
/**
 End of File
*/
