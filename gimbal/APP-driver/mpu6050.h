#ifndef __mpu_H
#define __mpu_H
#include "bsp_iic.h"
#define MPU_SAMPLE_RATE_REG		0X19	//����Ƶ�ʷ�Ƶ��
#define MPU_CFG_REG				0X1A	//���üĴ���
#define MPU_GYRO_CFG_REG		0X1B	//���������üĴ���
											//250	:	LSB=131
											//500	:	LSB=65.5
											//1000	:	LSB=32.8
											//2000	:	LSB=16.4
											
#define MPU_ACCEL_CFG_REG		0X1C	//���ٶȼ����üĴ���
											//2g	:	LSB=16384
											//4g	:	LSB=8192
											//8g	:	LSB=4096
											//16g	:	LSB=2048
											
#define MPU_MOTION_DET_REG		0X1F	//�˶���ֵⷧ���üĴ���
#define MPU_FIFO_EN_REG			0X23	//FIFOʹ�ܼĴ���
#define MPU_INTBP_CFG_REG		0X37	//�ж�/��·���üĴ���
#define MPU_INT_EN_REG			0X38	//�ж�ʹ�ܼĴ���
#define MPU_ACCEL_XOUTH_REG		0X3B	//���ٶ�ֵ,X���8λ�Ĵ���
#define MPU_ACCEL_XOUTL_REG		0X3C	//���ٶ�ֵ,X���8λ�Ĵ���
#define MPU_ACCEL_YOUTH_REG		0X3D	//���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU_ACCEL_YOUTL_REG		0X3E	//���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU_ACCEL_ZOUTH_REG		0X3F	//���ٶ�ֵ,Z���8λ�Ĵ���
#define MPU_ACCEL_ZOUTL_REG		0X40	//���ٶ�ֵ,Z���8λ�Ĵ���
#define MPU_TEMP_OUTH_REG		0X41	//�¶�ֵ��8λ�Ĵ���
#define MPU_TEMP_OUTL_REG		0X42	//�¶�ֵ��8λ�Ĵ���
#define MPU_GYRO_XOUTH_REG		0X43	//������ֵ,X���8λ�Ĵ���
#define MPU_GYRO_XOUTL_REG		0X44	//������ֵ,X���8λ�Ĵ���
#define MPU_GYRO_YOUTH_REG		0X45	//������ֵ,Y���8λ�Ĵ���
#define MPU_GYRO_YOUTL_REG		0X46	//������ֵ,Y���8λ�Ĵ���
#define MPU_GYRO_ZOUTH_REG		0X47	//������ֵ,Z���8λ�Ĵ���
#define MPU_GYRO_ZOUTL_REG		0X48	//������ֵ,Z���8λ�Ĵ���
#define MPU_USER_CTRL_REG		0X6A	//�û����ƼĴ���
#define MPU_PWR_MGMT1_REG		0X6B	//��Դ����Ĵ���1
#define MPU_PWR_MGMT2_REG		0X6C	//��Դ����Ĵ���2 
#define MPU_DEVICE_ID_REG		0X75	//����ID�Ĵ���

/*�ⲿ����*/
extern IIC_HandleTypeDef mpuIic;
uint8_t MPU_init(void);
uint8_t MPU_getG(float *gx, float *gy, float *gz);
unsigned char MPU_getA(float *ax, float *ay, float *az);

/*�ڲ�����*/
uint8_t MPU_writeData(uint8_t dev, uint8_t reg, uint8_t data);
uint8_t MPU_readData(uint8_t dev, uint8_t reg);
uint8_t MPU_writeLen(uint8_t dev, uint8_t reg, uint8_t len, uint8_t *buf);
uint8_t MPU_readLen(uint8_t dev, uint8_t reg, uint8_t len, uint8_t *buf);
#endif 

