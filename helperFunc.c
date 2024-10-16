/* Helper functions */

#include "helperFunc.h"
#include <stdio.h>
#include <string.h> // Include for memcpy

uint8_t dataBuffer[6];

uint8_t I2cWriteBuffer(uint8_t deviceAddr, uint8_t *buffer, uint16_t size )
{
    printf("Inputted Device Address: %x\n", deviceAddr);
    for(int i = 0; i < size; i++){
        dataBuffer[i] = buffer[i];
        printf("Buffer Byte %i: %02X\n", i, buffer[i]);
    }
    printf("Inputted Buffer Size: %u\n", size);
    
    return 0;
}

uint8_t I2cReadBuffer(uint8_t deviceAddr, uint8_t *buffer, uint16_t size )
{
    printf("Inputted Device Address: %x\n", deviceAddr);
    printf("Return Buffer Size, %u\n", size);
    
    // Buffer if reading dummy ID
    if(size == 2)
    {
        buffer[0] = 0x11;
        buffer[1] = 0x22;
    }
    // Buffer if reading dummy measurement
    else if(size == 4)
    {
        buffer[0] = 0x75;
        buffer[1] = 0x31;
        buffer[2] = 0x33;
        buffer[3] = 0x09;
    }
    else 
    {
        return 1;
    }

    
    return 0;
}