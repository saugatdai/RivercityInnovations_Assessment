/*
 * 
 * SHTC3 Temperature and Humidity Sensor I2C Driver
 * Author: Saugat Sigdel
 * Date Created: 2024 October 15
 * 
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SHTC3_I2C_DRIVER_H
#define SHTC3_I2C_DRIVER_H

#include <stdint.h>

/* DEFINES */

#define SHTC3_DEVICE_ADDRESS                            0X70
#define SHTC3_DEVICE_ID                                 0x1122 /* Device ID as dummy data provided by the helper function */

#define SHTC3_CMD_MEASURE_CLOCK_STRETCHING_ENABLED_MSB  0X7C /* Command Most Significant Byte for reading temperature first with clock stretching enabled  */
#define SHTC3_CMD_MEASURE_CLOCK_STRETCHING_ENABLED_LSB  0XA2 /* Command Least Significant Byte for reading temperature first with clock stretching enabled  */

#define SHTC3_CMD_WAKEUP_MSB                            0x35 /* Wake-up command Most Significant Byte */
#define SHTC3_CMD_WAKEUP_LSB                            0x17 /* Wake-up command Least Significant Byte */

#define SHTC3_CMD_SLEEP_MSB                             0xB0 /* Sleep command Most Significant Byte */
#define SHTC3_CMD_SLEEP_LSB                             0x98 /* Sleep command Least Significant Byte */

#define SHTC3_CMD_READ_ID_MSB                           0XEF /* Command Most Significant Byte to read out of ID Register */
#define SHTC3_CMD_READ_ID_LSB                           0XC8 /* Command Least Significant Byte to read out of ID Register */

/* The byte lengths used for reading and writing data with sensor register */
#define SHTC3_I2C_DATA_BYTE_LENGTH_2                    2
#define SHTC3_I2C_DATA_BYTE_LENGTH_4                    4

#define SHTC3_RESPONSE_DELAY                            0.0005  /* A small delay time of 500 micro-seconds given for SHTC3 to respond after writing a command to its register*/
#define SHTC3_WAKEUP_DELAY                              0.00024 /* Maximum wake up time for the SHTC3 Sensor is 240 micro-seconds according to datasheet */
#define SHTC3_MEASUREMENT_DELAY                         0.0121  /* Maximum time taken to make a measurement by the sonsor in normal mode of operation*/


typedef struct{
    float temp_C; /* Temperature Data in degree Centigrade*/
    float hum_RH; /* Humidity Data in %*/
} SHTC3_DATA;



/* DATA AQUISITION FUNCTIONS*/

/*!
 * \brief Read Temperature and Humidity in Standard Units
 *
 * \param [IN] *databuffer      data buffer to write the measured values
 */
uint8_t SHTC3_ReadSensorData(SHTC3_DATA *dataBuffer);

/*!
 * \brief Convert Raw Data of temperature and humidity to standard units
 *
 * \param [IN] temperature      Raw value of temperature measured from sensor
 * \param [IN] humidity         Raw value of humidity measured from the sensor
 */
SHTC3_DATA SHTC3_ConvertRawDataToStandard(uint16_t, uint16_t);



/* LOW LEVEL FUNCTIONS */

/*!
 * \brief Send Write command to SHTC3 Module via I2C
 *
 * \param [IN] *command         command to send to the module via I2C
 */
uint8_t SHTC3_WriteCommand(uint8_t *command);

/*!
 * \brief Check Sensor ID Number to verify correct communication/operation 
 */
uint8_t SHTC3_CheckCommunication();

/*!
 * \brief Send Wake Up command To the Sensor 
 */
uint8_t SHTC3_Wakeup();

/*!
 * \brief Send Sleep Command to the Sensor
 */
uint8_t SHTC3_Sleep();


#endif