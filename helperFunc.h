/* Helper functions */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HELPERFUNC_H_
#define HELPERFUNC_H_

#include <stdint.h>

/*!
 * \brief Write data buffer to the I2C device
 *
 * \param [IN] deviceAddr       device address
 * \param [IN] buffer           data buffer to write
 * \param [IN] size             number of bytes to write
 */
uint8_t I2cWriteBuffer(uint8_t deviceAddr, uint8_t *buffer, uint16_t size );

/*!
 * \brief Read data buffer from the I2C device
 *
 * \param [IN] obj              I2C object
 * \param [IN] deviceAddr       device address
 * \param [OUT] buffer          data buffer to read
 * \param [IN] size             number of data bytes to read
 */
uint8_t I2cReadBuffer(uint8_t deviceAddr, uint8_t *buffer, uint16_t size );

#endif