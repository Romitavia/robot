#ifndef __CANINFO_TASK_H
#define __CANINFO_TASK_H

#include "bsp_can.h"
#define YAW_MOTOR_ID			0x207
#define PITCH_MOTOR_ID		0x208
#define POKER_MOTOR_ID		0x201
#define SHOOT_LEFT_MOTOR_ID   0x204
#define SHOOT_RIGH_MOTOR_ID   0x202
#define REFEERE_DATA_ID		0x006

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
}Motor_HandleTypeDef;		

typedef struct
{
	int8_t robot_id;
	int16_t	heat0;
	int16_t	heat0_limit;	
	float   bullet_speed;
	uint8_t bullet_speedlimit;
	
}Refeere_HandleTypeDef;

extern Motor_HandleTypeDef yawMotor,pitchMotor,pokerMotor,shootMotor[2];

extern Refeere_HandleTypeDef		Refeere;
#endif
