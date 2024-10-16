#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#include "sensor.h"
#include "helperFunc.h"

uint8_t SHTC3_WriteCommand(uint8_t *command){
    uint8_t commandStatus;

    commandStatus = I2cWriteBuffer(SHTC3_DEVICE_ADDRESS, command, SHTC3_I2C_DATA_BYTE_LENGTH_2);
    if(commandStatus == 1){
        printf("Failed to write I2C command");
        return 1;
    }

    sleep(SHTC3_RESPONSE_DELAY);

    return 0;
}


uint8_t SHTC3_CheckCommunication()
{
    uint8_t deviceIDBuffer[SHTC3_I2C_DATA_BYTE_LENGTH_2];
    uint8_t command[] = {SHTC3_CMD_READ_ID_MSB, SHTC3_CMD_READ_ID_LSB};
    uint8_t commandStatus;
    uint16_t deviceID;

    commandStatus = SHTC3_WriteCommand(command);
    if(commandStatus == 1){
        return 1;
    }

    commandStatus = I2cReadBuffer(SHTC3_DEVICE_ADDRESS, deviceIDBuffer, SHTC3_I2C_DATA_BYTE_LENGTH_2);
    if(commandStatus == 1){
        printf("Failed to read I2C Data");
        return 1;
    }   

    /* Reversing and making 16-bit as the data arrived is in big endian order */
    deviceID = (deviceIDBuffer[0]<<8) | deviceIDBuffer[1];
    printf("Device ID Read: %04X", deviceID);

    if(deviceID != SHTC3_DEVICE_ID){
        printf("Communication Error");
        return 1;
    }
    
    return 0;
}


uint8_t SHTC3_Wakeup(){
    uint8_t command[] = {SHTC3_CMD_WAKEUP_MSB, SHTC3_CMD_WAKEUP_LSB};
    uint8_t commandStatus;

    commandStatus = SHTC3_WriteCommand(command);
    if(commandStatus == 1){
        return 1;
    }

    sleep(SHTC3_WAKEUP_DELAY);
    
    return 0;
}


uint8_t SHTC3_Sleep(){
    uint8_t command[] = {SHTC3_CMD_SLEEP_MSB, SHTC3_CMD_SLEEP_LSB};
    uint8_t commandStatus;

    commandStatus = SHTC3_WriteCommand(command);
    if(commandStatus == 1){
        return 1;
    }

    return 0;
}


uint8_t SHTC3_ReadSensorData(SHTC3_DATA *shtc3Data){
    uint8_t command[] = {SHTC3_CMD_MEASURE_CLOCK_STRETCHING_ENABLED_MSB, SHTC3_CMD_MEASURE_CLOCK_STRETCHING_ENABLED_LSB};
    uint8_t commandStatus;
    uint16_t temperatureRaw;
    uint16_t humidityRaw;
    uint8_t dataBuffer[SHTC3_I2C_DATA_BYTE_LENGTH_4];

    commandStatus = SHTC3_WriteCommand(command);
    if(commandStatus == 1){
        return 1;
    }
    sleep(SHTC3_MEASUREMENT_DELAY);

    commandStatus = I2cReadBuffer(SHTC3_DEVICE_ADDRESS, dataBuffer, SHTC3_I2C_DATA_BYTE_LENGTH_4);
    if(commandStatus == 1){
        printf("Failed to read temperature and humidity values");
        return 1;
    }

    /* Reversing and making 16-bit as the data arrived is in big endian order */
    temperatureRaw = dataBuffer[0] << 8 | dataBuffer[1];
    humidityRaw = dataBuffer[2] << 8 | dataBuffer[3];

    *shtc3Data = SHTC3_ConvertRawDataToStandard(temperatureRaw, humidityRaw);
    
    return 0;
}


SHTC3_DATA SHTC3_ConvertRawDataToStandard(uint16_t temperatureRaw, uint16_t humidityRaw){
    float temperature, humidity;
    SHTC3_DATA data;

    temperature = -45.0 + 175.0 * (float)temperatureRaw/65535.0;
    humidity = 100.0 * (float)humidityRaw/65535.0;

    /* Round into nearest tenth */
    data.temp_C = roundf(temperature*10)/10;
    data.hum_RH = roundf(humidity*10)/10;

    return data;
}