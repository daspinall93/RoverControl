// I2Cdev library collection - MPU6050 I2C device class
// Based on InvenSense MPU-6050 register map document rev. 2.0, 5/19/2011 (RM-MPU-6000A-00)
// 10/3/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//     ... - ongoing debug release

// NOTE: THIS IS ONLY A PARIAL RELEASE. THIS DEVICE CLASS IS CURRENTLY UNDERGOING ACTIVE
// DEVELOPMENT AND IS STILL MISSING SOME IMPORTANT FEATURES. PLEASE KEEP THIS IN MIND IF
// YOU DECIDE TO USE THIS PARTICULAR CODE FOR ANYTHING.

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2012 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

#ifndef _MPU6050_H_
#define _MPU6050_H_

#include "I2Cdev.h"
#include "../mavlink/SoteriaRover/mavlink.h"
#include "InertModuleConst.h"

class InertModule {
public:
	void Start();
	void Execute(mavlink_inert_report_t* p_InertReport_out);
	void CalibrateMPU();
	void Stop();

private:

	/* ACCELEROMETER ADC VALUES */
	int16_t accX_dig[MPU6050_MA_WINDOW_SIZE];
	int16_t accXAv_dig;
	int16_t accY_dig[MPU6050_MA_WINDOW_SIZE];
	int16_t accYAv_dig;
	int16_t accZ_dig[MPU6050_MA_WINDOW_SIZE];
	int16_t accZAv_dig;

	/* GYRO ADC VALUES */
	int16_t gyroX_dig[MPU6050_MA_WINDOW_SIZE];
	int16_t gyroXAv_dig;
	int16_t gyroY_dig[MPU6050_MA_WINDOW_SIZE];
	int16_t gyroYAv_dig;
	int16_t gyroZ_dig[MPU6050_MA_WINDOW_SIZE];
	int16_t gyroZAv_dig;

	/* BUFFER TO HOLD I2C COMMS DATA */
	uint8_t buffer[14];

	/* ADDRESS OF THE IMU ON 12C BUS */
	uint8_t devAddr;

	/* ANGLES */
	float accRoll_deg;
	float accPitch_deg;
	float gyroRoll_deg;
	float gyroPitch_deg;
	float gyroYaw_deg;

	/* RATES */
	float gyroXRate_degs;
	float gyroYRate_degs;
	float gyroZRate_degs;

	/* TILT FLAG FOR FDIR */
	uint8_t tiltFlag;

	/* TIME */
	long int prevCall;
	long int currentCall;

	/* LOCALISATION FUNCTIONS */
    void UpdateAnglesGyro();
    void UpdateAnglesAcc();

	/* ACC AND GYRO SAMPLING FUNCTIONS */
	void UpdateWindow();
	void UpdateAverages();
	void UpdateReport(mavlink_inert_report_t* p_InertReport_out);
	void Debug();

	/* MPU6050 LIBRARY */
	bool testConnection();

	// AUX_VDDIO register
	uint8_t getAuxVDDIOLevel();
	void setAuxVDDIOLevel(uint8_t level);

	// SMPLRT_DIV register
	uint8_t getRate();
	void setRate(uint8_t rate);

	// CONFIG register
	uint8_t getExternalFrameSync();
	void setExternalFrameSync(uint8_t sync);
	uint8_t getDLPFMode();
	void setDLPFMode(uint8_t bandwidth);

	// GYRO_CONFIG register
	uint8_t getFullScaleGyroRange();
	void setFullScaleGyroRange(uint8_t range);

	// SELF_TEST registers
	uint8_t getAccelXSelfTestFactoryTrim();
	uint8_t getAccelYSelfTestFactoryTrim();
	uint8_t getAccelZSelfTestFactoryTrim();

	uint8_t getGyroXSelfTestFactoryTrim();
	uint8_t getGyroYSelfTestFactoryTrim();
	uint8_t getGyroZSelfTestFactoryTrim();

	// ACCEL_CONFIG register
	bool getAccelXSelfTest();
	void setAccelXSelfTest(bool enabled);
	bool getAccelYSelfTest();
	void setAccelYSelfTest(bool enabled);
	bool getAccelZSelfTest();
	void setAccelZSelfTest(bool enabled);
	uint8_t getFullScaleAccelRange();
	void setFullScaleAccelRange(uint8_t range);
	uint8_t getDHPFMode();
	void setDHPFMode(uint8_t mode);

	// FF_THR register
	uint8_t getFreefallDetectionThreshold();
	void setFreefallDetectionThreshold(uint8_t threshold);

	// FF_DUR register
	uint8_t getFreefallDetectionDuration();
	void setFreefallDetectionDuration(uint8_t duration);

	// MOT_THR register
	uint8_t getMotionDetectionThreshold();
	void setMotionDetectionThreshold(uint8_t threshold);

	// MOT_DUR register
	uint8_t getMotionDetectionDuration();
	void setMotionDetectionDuration(uint8_t duration);

	// ZRMOT_THR register
	uint8_t getZeroMotionDetectionThreshold();
	void setZeroMotionDetectionThreshold(uint8_t threshold);

	// ZRMOT_DUR register
	uint8_t getZeroMotionDetectionDuration();
	void setZeroMotionDetectionDuration(uint8_t duration);

	// FIFO_EN register
	bool getTempFIFOEnabled();
	void setTempFIFOEnabled(bool enabled);
	bool getXGyroFIFOEnabled();
	void setXGyroFIFOEnabled(bool enabled);
	bool getYGyroFIFOEnabled();
	void setYGyroFIFOEnabled(bool enabled);
	bool getZGyroFIFOEnabled();
	void setZGyroFIFOEnabled(bool enabled);
	bool getAccelFIFOEnabled();
	void setAccelFIFOEnabled(bool enabled);
	bool getSlave2FIFOEnabled();
	void setSlave2FIFOEnabled(bool enabled);
	bool getSlave1FIFOEnabled();
	void setSlave1FIFOEnabled(bool enabled);
	bool getSlave0FIFOEnabled();
	void setSlave0FIFOEnabled(bool enabled);

	// I2C_MST_CTRL register
	bool getMultiMasterEnabled();
	void setMultiMasterEnabled(bool enabled);
	bool getWaitForExternalSensorEnabled();
	void setWaitForExternalSensorEnabled(bool enabled);
	bool getSlave3FIFOEnabled();
	void setSlave3FIFOEnabled(bool enabled);
	bool getSlaveReadWriteTransitionEnabled();
	void setSlaveReadWriteTransitionEnabled(bool enabled);
	uint8_t getMasterClockSpeed();
	void setMasterClockSpeed(uint8_t speed);

	// I2C_SLV* registers (Slave 0-3)
	uint8_t getSlaveAddress(uint8_t num);
	void setSlaveAddress(uint8_t num, uint8_t address);
	uint8_t getSlaveRegister(uint8_t num);
	void setSlaveRegister(uint8_t num, uint8_t reg);
	bool getSlaveEnabled(uint8_t num);
	void setSlaveEnabled(uint8_t num, bool enabled);
	bool getSlaveWordByteSwap(uint8_t num);
	void setSlaveWordByteSwap(uint8_t num, bool enabled);
	bool getSlaveWriteMode(uint8_t num);
	void setSlaveWriteMode(uint8_t num, bool mode);
	bool getSlaveWordGroupOffset(uint8_t num);
	void setSlaveWordGroupOffset(uint8_t num, bool enabled);
	uint8_t getSlaveDataLength(uint8_t num);
	void setSlaveDataLength(uint8_t num, uint8_t length);

	// I2C_SLV* registers (Slave 4)
	uint8_t getSlave4Address();
	void setSlave4Address(uint8_t address);
	uint8_t getSlave4Register();
	void setSlave4Register(uint8_t reg);
	void setSlave4OutputByte(uint8_t data);
	bool getSlave4Enabled();
	void setSlave4Enabled(bool enabled);
	bool getSlave4InterruptEnabled();
	void setSlave4InterruptEnabled(bool enabled);
	bool getSlave4WriteMode();
	void setSlave4WriteMode(bool mode);
	uint8_t getSlave4MasterDelay();
	void setSlave4MasterDelay(uint8_t delay);
	uint8_t getSlate4InputByte();

	// I2C_MST_STATUS register
	bool getPassthroughStatus();
	bool getSlave4IsDone();
	bool getLostArbitration();
	bool getSlave4Nack();
	bool getSlave3Nack();
	bool getSlave2Nack();
	bool getSlave1Nack();
	bool getSlave0Nack();

	// INT_PIN_CFG register
	bool getInterruptMode();
	void setInterruptMode(bool mode);
	bool getInterruptDrive();
	void setInterruptDrive(bool drive);
	bool getInterruptLatch();
	void setInterruptLatch(bool latch);
	bool getInterruptLatchClear();
	void setInterruptLatchClear(bool clear);
	bool getFSyncInterruptLevel();
	void setFSyncInterruptLevel(bool level);
	bool getFSyncInterruptEnabled();
	void setFSyncInterruptEnabled(bool enabled);
	bool getI2CBypassEnabled();
	void setI2CBypassEnabled(bool enabled);
	bool getClockOutputEnabled();
	void setClockOutputEnabled(bool enabled);

	// INT_ENABLE register
	uint8_t getIntEnabled();
	void setIntEnabled(uint8_t enabled);
	bool getIntFreefallEnabled();
	void setIntFreefallEnabled(bool enabled);
	bool getIntMotionEnabled();
	void setIntMotionEnabled(bool enabled);
	bool getIntZeroMotionEnabled();
	void setIntZeroMotionEnabled(bool enabled);
	bool getIntFIFOBufferOverflowEnabled();
	void setIntFIFOBufferOverflowEnabled(bool enabled);
	bool getIntI2CMasterEnabled();
	void setIntI2CMasterEnabled(bool enabled);
	bool getIntDataReadyEnabled();
	void setIntDataReadyEnabled(bool enabled);

	// INT_STATUS register
	uint8_t getIntStatus();
	bool getIntFreefallStatus();
	bool getIntMotionStatus();
	bool getIntZeroMotionStatus();
	bool getIntFIFOBufferOverflowStatus();
	bool getIntI2CMasterStatus();
	bool getIntDataReadyStatus();

	// ACCEL_*OUT_* registers
	void getMotion9(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz, int16_t* mx, int16_t* my, int16_t* mz);
	void getMotion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);
	void getAcceleration(int16_t* x, int16_t* y, int16_t* z);
	int16_t getAccelerationX();
	int16_t getAccelerationY();
	int16_t getAccelerationZ();

	// TEMP_OUT_* registers
	int16_t getTemperature();

	// GYRO_*OUT_* registers
	void getRotation(int16_t* x, int16_t* y, int16_t* z);
	int16_t getRotationX();
	int16_t getRotationY();
	int16_t getRotationZ();

	// EXT_SENS_DATA_* registers
	uint8_t getExternalSensorByte(int position);
	uint16_t getExternalSensorWord(int position);
	uint32_t getExternalSensorDWord(int position);

	// MOT_DETECT_STATUS register
	uint8_t getMotionStatus();
	bool getXNegMotionDetected();
	bool getXPosMotionDetected();
	bool getYNegMotionDetected();
	bool getYPosMotionDetected();
	bool getZNegMotionDetected();
	bool getZPosMotionDetected();
	bool getZeroMotionDetected();

	// I2C_SLV*_DO register
	void setSlaveOutputByte(uint8_t num, uint8_t data);

	// I2C_MST_DELAY_CTRL register
	bool getExternalShadowDelayEnabled();
	void setExternalShadowDelayEnabled(bool enabled);
	bool getSlaveDelayEnabled(uint8_t num);
	void setSlaveDelayEnabled(uint8_t num, bool enabled);

	// SIGNAL_PATH_RESET register
	void resetGyroscopePath();
	void resetAccelerometerPath();
	void resetTemperaturePath();

	// MOT_DETECT_CTRL register
	uint8_t getAccelerometerPowerOnDelay();
	void setAccelerometerPowerOnDelay(uint8_t delay);
	uint8_t getFreefallDetectionCounterDecrement();
	void setFreefallDetectionCounterDecrement(uint8_t decrement);
	uint8_t getMotionDetectionCounterDecrement();
	void setMotionDetectionCounterDecrement(uint8_t decrement);

	// USER_CTRL register
	bool getFIFOEnabled();
	void setFIFOEnabled(bool enabled);
	bool getI2CMasterModeEnabled();
	void setI2CMasterModeEnabled(bool enabled);
	void switchSPIEnabled(bool enabled);
	void resetFIFO();
	void resetI2CMaster();
	void resetSensors();

	// PWR_MGMT_1 register
	void reset();
	bool getSleepEnabled();
	void setSleepEnabled(bool enabled);
	bool getWakeCycleEnabled();
	void setWakeCycleEnabled(bool enabled);
	bool getTempSensorEnabled();
	void setTempSensorEnabled(bool enabled);
	uint8_t getClockSource();
	void setClockSource(uint8_t source);

	// PWR_MGMT_2 register
	uint8_t getWakeFrequency();
	void setWakeFrequency(uint8_t frequency);
	bool getStandbyXAccelEnabled();
	void setStandbyXAccelEnabled(bool enabled);
	bool getStandbyYAccelEnabled();
	void setStandbyYAccelEnabled(bool enabled);
	bool getStandbyZAccelEnabled();
	void setStandbyZAccelEnabled(bool enabled);
	bool getStandbyXGyroEnabled();
	void setStandbyXGyroEnabled(bool enabled);
	bool getStandbyYGyroEnabled();
	void setStandbyYGyroEnabled(bool enabled);
	bool getStandbyZGyroEnabled();
	void setStandbyZGyroEnabled(bool enabled);

	// FIFO_COUNT_* registers
	uint16_t getFIFOCount();

	// FIFO_R_W register
	uint8_t getFIFOByte();
	void setFIFOByte(uint8_t data);
	void getFIFOBytes(uint8_t *data, uint8_t length);

	// WHO_AM_I register
	uint8_t getDeviceID();
	void setDeviceID(uint8_t id);

	// ======== UNDOCUMENTED/DMP REGISTERS/METHODS ========

	// XG_OFFS_TC register
	uint8_t getOTPBankValid();
	void setOTPBankValid(bool enabled);
	int8_t getXGyroOffsetTC();
	void setXGyroOffsetTC(int8_t offset);

	// YG_OFFS_TC register
	int8_t getYGyroOffsetTC();
	void setYGyroOffsetTC(int8_t offset);

	// ZG_OFFS_TC register
	int8_t getZGyroOffsetTC();
	void setZGyroOffsetTC(int8_t offset);

	// X_FINE_GAIN register
	int8_t getXFineGain();
	void setXFineGain(int8_t gain);

	// Y_FINE_GAIN register
	int8_t getYFineGain();
	void setYFineGain(int8_t gain);

	// Z_FINE_GAIN register
	int8_t getZFineGain();
	void setZFineGain(int8_t gain);

	// XA_OFFS_* registers
	int16_t getXAccelOffset();
	void setXAccelOffset(int16_t offset);

	// YA_OFFS_* register
	int16_t getYAccelOffset();
	void setYAccelOffset(int16_t offset);

	// ZA_OFFS_* register
	int16_t getZAccelOffset();
	void setZAccelOffset(int16_t offset);

	// XG_OFFS_USR* registers
	int16_t getXGyroOffset();
	void setXGyroOffset(int16_t offset);

	// YG_OFFS_USR* register
	int16_t getYGyroOffset();
	void setYGyroOffset(int16_t offset);

	// ZG_OFFS_USR* register
	int16_t getZGyroOffset();
	void setZGyroOffset(int16_t offset);

	// INT_ENABLE register (DMP functions)
	bool getIntPLLReadyEnabled();
	void setIntPLLReadyEnabled(bool enabled);
	bool getIntDMPEnabled();
	void setIntDMPEnabled(bool enabled);

	// DMP_INT_STATUS
	bool getDMPInt5Status();
	bool getDMPInt4Status();
	bool getDMPInt3Status();
	bool getDMPInt2Status();
	bool getDMPInt1Status();
	bool getDMPInt0Status();

	// INT_STATUS register (DMP functions)
	bool getIntPLLReadyStatus();
	bool getIntDMPStatus();

	// USER_CTRL register (DMP functions)
	bool getDMPEnabled();
	void setDMPEnabled(bool enabled);
	void resetDMP();

	// BANK_SEL register
	void setMemoryBank(uint8_t bank, bool prefetchEnabled=false, bool userBank=false);

	// MEM_START_ADDR register
	void setMemoryStartAddress(uint8_t address);

	// MEM_R_W register
	uint8_t readMemoryByte();
	void writeMemoryByte(uint8_t data);
	void readMemoryBlock(uint8_t *data, uint16_t dataSize, uint8_t bank=0, uint8_t address=0);
	bool writeMemoryBlock(const uint8_t *data, uint16_t dataSize, uint8_t bank=0, uint8_t address=0, bool verify=true, bool useProgMem=false);
	bool writeProgMemoryBlock(const uint8_t *data, uint16_t dataSize, uint8_t bank=0, uint8_t address=0, bool verify=true);

	bool writeDMPConfigurationSet(const uint8_t *data, uint16_t dataSize, bool useProgMem=false);
	bool writeProgDMPConfigurationSet(const uint8_t *data, uint16_t dataSize);

	// DMP_CFG_1 register
	uint8_t getDMPConfig1();
	void setDMPConfig1(uint8_t config);

	// DMP_CFG_2 register
	uint8_t getDMPConfig2();
	void setDMPConfig2(uint8_t config);

};

#endif /* _MPU6050_H_ */
