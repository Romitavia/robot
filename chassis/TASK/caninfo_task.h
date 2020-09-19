#ifndef __CANINFO_TASK_H
#define __CANINFO_TASK_H

#include "can.h"

#define CHASSIS_LF_MOTOR_CAN_ID         0x201
#define CHASSIS_LB_MOTOR_CAN_ID         0x202
#define CHASSIS_RF_MOTOR_CAN_ID         0x203
#define CHASSIS_RB_MOTOR_CAN_ID         0x204
#define CHASSIS_YAW_MOTOR_CAN_ID        0x207
#define CHASSIS_CONTROL_MAIL_ID         0x007
typedef struct
{
	uint16_t    lastCoder; /*�ϴε��ת�ӱ�����ֵ*/
	
	float 			sumCoder;/*���ת�ӱ�����ֵ�ۼƺ�*/
	
	uint16_t 		coder;/*���ʵʱת�ӱ�����ֵ*/
	
	float				coderTarget;/*λ�û�������*/
	
	int16_t		  speed;/*���ʵʱ�ٶ�*/
	
	float       speedTarget;/*�ٶȻ�������*/
	
	uint8_t     temp; /*����¶�*/
	
	int32_t 		turns;/*������ϵ翪ʼת����Ȧ��*/
	
	int16_t       current;/*�������*/
}Motor_HandleTypeDef;	

typedef struct 
{
	int16_t x;
	int16_t y;
	int8_t  s0;
	int8_t  mode;
	int8_t  superstate;
}Control_HandleTypeDef;

extern Motor_HandleTypeDef chassisMotor[4],yawMotor;
extern Control_HandleTypeDef	chassisCan;
#endif
