#define ACCEL_CONFIG 0x14
#define ACCEL_XOUT_H 0x2D
#define ACCEL_XOUT_L 0x2E
#define ACCEL_YOUT_H 0x2F
#define ACCEL_YOUT_L 0x30
#define ACCEL_ZOUT_H 0x31
#define ACCEL_ZOUT_L 0x32
#define GYRO_CONFIG  0x01
#define GYRO_XOUT_H  0x33
#define GYRO_XOUT_L  0x34
#define GYRO_YOUT_H  0x35
#define GYRO_YOUT_L  0x36
#define GYRO_ZOUT_H  0x37
#define GYRO_ZOUT_L  0x38
#define FIFO_R_W     0x72
#define XA_OFFS_H    0x14
#define XA_OFFS_L    0x15
#define YA_OFFS_H    0x17
#define YA_OFFS_L    0x18
#define ZA_OFFS_H    0x1A
#define ZA_OFFS_L    0x1B
#define XG_OFFS_USRH 0x03
#define XG_OFFS_USRL 0x04
#define YG_OFFS_USRH 0x05
#define YG_OFFS_USRL 0x06
#define ZG_OFFS_USRH 0x07
#define ZG_OFFS_USRL 0x08

#define ACCEL_RANGE_2   0x29
#define ACCEL_RANGE_4   0x2B
#define GYRO_RANGE_250  0x11
#define GYRO_RANGE_500  0x13

#define ACCEL_SENSITIVITY_2    16384
#define ACCEL_SENSITIVITY_4    8192
#define GYRO_SENSITIVITY_250   131
#define GYRO_SENSITIVITY_500   65.5

#define PWR_MNG     0x06
#define PWR_MNG_2   0x07
#define USER_CTRL   0x03
#define USER_BANK_0 0x00
#define USER_BANK_1 0x08
#define USER_BANK_2 0x10
#define USER_BANK_3 0x18

#define XACCEL_OFFSET  0
#define YACCEL_OFFSET  0
#define ZACCEL_OFFSET  0
#define XGYRO_OFFSET   0
#define YGYRO_OFFSET   0
#define ZGYRO_OFFSET   0

#define LOW_PASS_ALPHA  0.8
#define COMP_FILT_ALPHA 0.96
