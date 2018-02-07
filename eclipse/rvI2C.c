/*
 * RVSW_IO.c
 * Use BCM2835 library to interact with motors and sensors
 *
 *  Created on: 13 Jan 2018
 *      Author: D.Aspinall
 */

#include "rvI2C.h"

int i2c_baud = 100000;	//baud rate used for i2c bus


/* I2C functions */

/*
 * Enable or disable i2c
 */

void i2c_enable(){

	//setup baudrate and enable
	//bcm2835_i2c_set_baudrate( i2c_baud );
	bcm2835_i2c_begin();

}

void i2c_disable(){

	bcm2835_i2c_end();

}

//buffers for holding data to be transferred and received
char i2c_send_buf[256];
char i2c_recv_buf[256];

/** Read a single bit from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param bitNum Bit position to read (0-7)
 * @param data Container for single bit value
 * @return Status of read operation (true = success)
 */
int8_t i2c_readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data) {
  bcm2835_i2c_setSlaveAddress(devAddr);
  i2c_send_buf[0] = regAddr;
  uint8_t response = bcm2835_i2c_write_read_rs(i2c_send_buf, 1, i2c_recv_buf, 1);
  *data = i2c_recv_buf[1] & (1 << bitNum);
  return response == BCM2835_I2C_REASON_OK ;	//checking the response from read_rs is 0 (success)
}

/** Read multiple bits from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param bitStart First bit position to read (0-7)
 * @param length Number of bits to read (not more than 8)
 * @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
 * @return Status of read operation (true = success)
 */
int8_t i2c_readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data) {
  // 01101001 read byte
  // 76543210 bit numbers
  //    xxx   args: bitStart=4, length=3
  //    010   masked
  //   -> 010 shifted
  bcm2835_i2c_setSlaveAddress(devAddr);
  i2c_send_buf[0] = regAddr;
  uint8_t response = bcm2835_i2c_write_read_rs(i2c_send_buf, 1, i2c_recv_buf, 1);
  uint8_t b = (uint8_t) i2c_recv_buf[0];
  if (response == BCM2835_I2C_REASON_OK) {
    uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    b &= mask;
    b >>= (bitStart - length + 1);
    *data = b;
  }
  return response == BCM2835_I2C_REASON_OK;
}

/** Read single byte from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param data Container for byte value read from device
 * @return Status of read operation (true = success)
 */
int8_t i2c_readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data) {
  bcm2835_i2c_setSlaveAddress(devAddr);
  i2c_send_buf[0] = regAddr;
  uint8_t response = bcm2835_i2c_write_read_rs(i2c_send_buf, 1, i2c_recv_buf, 1);
  data[0] = (uint8_t) i2c_recv_buf[0];
  return response == BCM2835_I2C_REASON_OK;
}

/** Read multiple bytes from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr First register regAddr to read from
 * @param length Number of bytes to read
 * @param data Buffer to store read data in
 * @return I2C_TransferReturn_TypeDef http://downloads.energymicro.com/documentation/doxygen/group__I2C.html
 */
int8_t i2c_readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data) {
  bcm2835_i2c_setSlaveAddress(devAddr);
  i2c_send_buf[0] = regAddr;
  uint8_t response = bcm2835_i2c_write_read_rs(i2c_send_buf, 1, i2c_recv_buf, length);
  int i ;
  for (i = 0; i < length ; i++) {
    data[i] = (uint8_t) i2c_recv_buf[i];
  }
  return response == BCM2835_I2C_REASON_OK;
}

/** write a single bit in an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitNum Bit position to write (0-7)
 * @param value New bit value to write
 * @return Status of operation (true = success)
 */
int8_t i2c_writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data) {
  bcm2835_i2c_setSlaveAddress(devAddr);
  //first reading registery value
  i2c_send_buf[0] = regAddr;
  uint8_t response = bcm2835_i2c_write_read_rs(i2c_send_buf, 1, i2c_recv_buf, 1 );
  if ( response == BCM2835_I2C_REASON_OK ) {
    uint8_t b = i2c_recv_buf[0] ;
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    i2c_send_buf[1] = b ;
    response = bcm2835_i2c_write(i2c_send_buf, 2);
  }
  return response == BCM2835_I2C_REASON_OK;
}

/** Write multiple bits in an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitStart First bit position to write (0-7)
 * @param length Number of bits to write (not more than 8)
 * @param data Right-aligned value to write
 * @return Status of operation (true = success)
 */
int8_t i2c_writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) {
  //      010 value to write
  // 76543210 bit numbers
  //    xxx   args: bitStart=4, length=3
  // 00011100 mask byte
  // 10101111 original value (sample)
  // 10100011 original & ~mask
  // 10101011 masked | value
  bcm2835_i2c_setSlaveAddress(devAddr);
  //first reading registery value
  i2c_send_buf[0] = regAddr;
  uint8_t response = bcm2835_i2c_write_read_rs(i2c_send_buf, 1, i2c_recv_buf, 1 );
  if ( response == BCM2835_I2C_REASON_OK ) {
    uint8_t b = i2c_recv_buf[0];
    uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    data <<= (bitStart - length + 1); // shift data into correct position
    data &= mask; // zero all non-important bits in data
    b &= ~(mask); // zero all important bits in existing byte
    b |= data; // combine data with existing byte
    i2c_send_buf[1] = b ;
    response = bcm2835_i2c_write(i2c_send_buf, 2);
    }
  return response == BCM2835_I2C_REASON_OK;
}

/** Write single byte to an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register address to write to
 * @param data New byte value to write
 * @return Status of operation (true = success)
 */
int8_t i2c_writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data) {
  bcm2835_i2c_setSlaveAddress(devAddr);
  i2c_send_buf[0] = regAddr;
  i2c_send_buf[1] = data;
  uint8_t response = bcm2835_i2c_write(i2c_send_buf, 2);
  return response == BCM2835_I2C_REASON_OK ;
}

/** Read single word from a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param data Container for word value read from device
 * @return Status of read operation (true = success)
 */
int8_t i2c_readWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data) {
  bcm2835_i2c_setSlaveAddress(devAddr);
  i2c_send_buf[0] = regAddr;
  uint8_t response = bcm2835_i2c_write_read_rs(i2c_send_buf, 1, i2c_recv_buf, 2 );
  data[0] = (i2c_recv_buf[0] << 8) | i2c_recv_buf[1] ;
  return  response == BCM2835_I2C_REASON_OK ;
}

/** Read multiple words from a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr First register regAddr to read from
 * @param length Number of words to read
 * @param data Buffer to store read data in
 * @return Number of words read (-1 indicates failure)
 */
int8_t i2c_readWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data) {
  bcm2835_i2c_setSlaveAddress(devAddr);
  i2c_send_buf[0] = regAddr;
  uint8_t response = bcm2835_i2c_write_read_rs(i2c_send_buf, 1, i2c_recv_buf, length*2 );
  uint8_t i;
  for (i = 0; i < length; i++) {
    data[i] = (i2c_recv_buf[i*2] << 8) | i2c_recv_buf[i*2+1] ;
  }
  return  response == BCM2835_I2C_REASON_OK ;
}

int8_t i2c_writeWord(uint8_t devAddr, uint8_t regAddr, uint16_t data){
  bcm2835_i2c_setSlaveAddress(devAddr);
  i2c_send_buf[0] = regAddr;
  i2c_send_buf[1] = (uint8_t) (data >> 8); //MSByte
  i2c_send_buf[2] = (uint8_t) (data >> 0); //LSByte
  uint8_t response = bcm2835_i2c_write(i2c_send_buf, 3);
  return response == BCM2835_I2C_REASON_OK ;
}

int8_t i2c_writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data){
  bcm2835_i2c_setSlaveAddress(devAddr);
  i2c_send_buf[0] = regAddr;
  uint8_t i;
  for (i = 0; i < length; i++) {
    i2c_send_buf[i+1] = data[i] ;
  }
  uint8_t response = bcm2835_i2c_write(i2c_send_buf, 1+length);
  return response == BCM2835_I2C_REASON_OK ;
}

int8_t i2c_writeWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data){
  bcm2835_i2c_setSlaveAddress(devAddr);
  i2c_send_buf[0] = regAddr;
  uint8_t i;
  for (i = 0; i < length; i++) {
    i2c_send_buf[1+2*i] = (uint8_t) (data[i] >> 8); //MSByte
    i2c_send_buf[2+2*i] = (uint8_t) (data[i] >> 0); //LSByte
  }
  uint8_t response = bcm2835_i2c_write(i2c_send_buf, 1+2*length);
  return response == BCM2835_I2C_REASON_OK ;
}


