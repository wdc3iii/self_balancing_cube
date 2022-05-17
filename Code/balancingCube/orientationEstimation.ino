#include "orientationHeader.h"
#include <SPI.h>


const uint8_t IMU_CHIP_SELECT = 10;
volatile float thetaY;
volatile int accelX;
volatile int accelZ;


void setup() {
    pinMode(IMU_CHIP_SELECT, OUTPUT);
    SPI.begin(); 
    
    // IMU Setup
    spi_IMU_write8(PWR_MNG, 0x80);  // Reset IMU
    delay(3000);
    spi_IMU_write8(PWR_MNG, 0x02);  // Select IMU clock
    spi_IMU_write8(USER_CTRL, 0xD0);
    // Set Gyro, Accel sensitivity, DLPF
    spi_IMU_setUserBank(USER_BANK_2);
    spi_IMU_write8(GYRO_CONFIG, GYRO_RANGE_250);
    spi_IMU_write8(ACCEL_CONFIG, ACCEL_RANGE_2);
    // Set power state
    uint8_t check1 = spi_IMU_read8(GYRO_CONFIG);
    uint8_t check2 = spi_IMU_read8(ACCEL_CONFIG);
    printf("%d", check1);
    printf("%d", check1);
    spi_IMU_setUserBank(USER_BANK_0);
}

void loop() {
    short data[3];
    float dt = 0.01;
    IMUGetData(&data);
    accelX = (1 - LOW_PASS_ALPHA) * data[0] + LOW_PASS_ALPHA * accelX;
    accelZ = (1 - LOW_PASS_ALPHA) * data[1] + LOW_PASS_ALPHA * accelZ;
    float thetaAccel = - atan2f((float) accelX, (float) accelZ) * 180 / M_PI;
    float gyroAccel = thetaY + data[2] * dt / GYRO_SENSITIVITY_250;
    thetaY = COMP_FILT_ALPHA * gyroAccel + (1 - COMP_FILT_ALPHA) * thetaAccel;
    Serial.println(thetaY);
}

void spi_IMU_setUserBank(uint8_t bank) {
    uint8_t reg = ~0x80 & 0xF7;
    digitalWrite(IMU_CHIP_SELECT, LOW);  // Set Slave select to low to begin transmission
    SPI.transfer(reg);                   // Tranfer the register
    SPI.transfer(bank);                  // Transfer the bank to select
    digitalWrite(IMU_CHIP_SELECT, HIGH); // Set slave select high
}

uint8_t spi_IMU_read8(uint8_t reg) {
    reg |= 0x80;                         // Set high bit on register to indicate read action
    digitalWrite(IMU_CHIP_SELECT, LOW);  // Set Slave select to low to begin transmission
    SPI.transfer(reg);                   // Transmit register to read from
    uint8_t RXData = SPI.transfer(0x00); // Send clock pulses, to receive data
    digitalWrite(IMU_CHIP_SELECT, HIGH); // Set slave select high
    return RXData;
}

short spi_IMU_read16(uint8_t regHigh, uint8_t regLow) {
    reg |= 0x80;                           // Set high bit on register to indicate read action
    digitalWrite(IMU_CHIP_SELECT, LOW);    // Set Slave select to low to begin transmission
    SPI.transfer(regHigh);                 // Transmit register to read from
    uint8_t highData = SPI.transfer(0x00); // Send clock pulses, to receive data
    SPI.transfer(regLow);                  // Transmit register to read from
    uint8_t lowData = SPI.transfer(0x00);  // Send clock pulses, to receive data
    digitalWrite(IMU_CHIP_SELECT, HIGH);   // Set slave select high
    short data = highData << 8 | lowData;  // Convert 8bit data into 16bit int
    return data;
}

void spi_IMU_write8(uint8_t reg, uint8_t value) {
    reg &= ~0x80;                        // Set high bit low on register to indicate write action
    digitalWrite(IMU_CHIP_SELECT, LOW);  // Set Slave select to low to begin transmission
    SPI.transfer(reg);                   // Transmit register to read from
    SPI.transfer(value);                 // Send clock pulses, to receive data
    digitalWrite(IMU_CHIP_SELECT, HIGH); // Set slave select high
}

void IMUGetData(short *data) {
    *data = spi_IMU_read16(ACCEL_XOUT_H, ACCEL_XOUT_L) + XACCEL_OFFSET;       // Form Accel X
    *(data + 1) = spi_IMU_read16(ACCEL_ZOUT_H, ACCEL_ZOUT_L) + ZACCEL_OFFSET; // Form Accel Z
    *(data + 2) = spi_IMU_read16(GYRO_YOUT_H, GYRO_YOUT_L) + YGYRO_OFFSET;    // Form Gyro Y
}
