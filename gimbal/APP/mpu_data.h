#ifndef __MPU_DATA_H
#define __MPU_DATA_H

#include "main.h"
#include "mpu6050.h"
#include "usart.h"
#include <math.h>

#define GIMBAL_GYRO_X_OFFSET            -1.8561f//-3.2927f                      //����������x�᷽��ƫ����(��̨)
#define GIMBAL_GYRO_Y_OFFSET	    	      1.660460f//0.7927f                     //����������y�᷽��ƫ����(��̨)
#define GIMBAL_GYRO_Z_OFFSET            -1.3146f//-3.3902f                      //����������z�᷽��ƫ����(��̨)

#define GIMBAL_ANGLE_PITCH_INIT         -24.20f                      //����������pitch����Ƕȳ�ʼֵ(��̨)
#define GIMBAL_ANGLE_ROLL_INIT           0.0f                        //����������roll����Ƕȳ�ʼֵ(��̨)
#define GIMBAL_ANGLE_YAW_INIT            0.0f                        //����������yaw����Ƕȳ�ʼֵ(��̨)

#define GIMBAL_GYRO_X_ZERO_CORRECT       0.5f                        //����������x�᷽����������(��̨)
#define GIMBAL_GYRO_Y_ZERO_CORRECT       0.3f                        //����������y�᷽����������(��̨)
#define GIMBAL_GYRO_Z_ZERO_CORRECT       0.4f                        //����������z�᷽����������(��̨)

#define GIMBAL_ANGLE_PITCH_ZERO_CORRECT       0.8f                        //����������PITCH�᷽����������(��̨)
#define GIMBAL_ANGLE_YAW_ZERO_CORRECT         1.5f                        //����������YAW�᷽����������(��̨)
#define GIMBAL_ANGLE_ROLL_ZERO_CORRECT        1.5f                        //����������ROLL������������(��̨)

typedef struct
{
	float gx; 
	float gy;
	float gz;
	
	unsigned char status;
	float gzOffset;
	float gyOffset;
	
	float ax; 
	float ay;
	float az;
	
	float yaw;


}MPUDataType;

extern MPUDataType mpuData;
uint8_t Gimbal_MpuUpdate(void);
float Updata_MPU6050_AngleContinuation(float MpuDataGimbalAngle);


#endif
