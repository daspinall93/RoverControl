/*
 * RVSW_IO.h
 *
 *  Created on: 14 Jan 2018
 *      Author: dan
 */

#ifndef RVI2C_H_
#define RVI2C_H_

#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include <bcm2835.h>

//i2c functions (IMU)
void i2c_enable();
void i2c_disable();

//reading and writing data to devices on bus
int8_t i2c_readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data);
int8_t i2c_readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data);
int8_t i2c_readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data);
int8_t i2c_readWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data);
int8_t i2c_readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);
int8_t i2c_readWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data);
int8_t i2c_writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);
int8_t i2c_writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);
int8_t i2c_writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
int8_t i2c_writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);
int8_t i2c_writeWord(uint8_t devAddr, uint8_t regAddr, uint16_t data);
int8_t i2c_writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);
int8_t i2c_writeWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data);


#endif /* RVSW_IO_H_ */

