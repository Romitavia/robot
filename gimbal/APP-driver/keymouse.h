#ifndef __KEYMOUSE_H_
#define __KEYMOUSE_H_

#include "rc.h"

/*Driver_KeyMouse Command Define*/
//------------------------------------------------------------------------------|
//����ֵ��  Q       |   W       |   E       |   R       |           |           |
//��Ӧλ��  bit[6]  |   bit[0]  |   bit[7]  |   bit[8]  |           |           |
//------------------------------------------------------------------------------|
//����ֵ��  A       |   S       |   D       |   F       |   G       |           |
//��Ӧλ��  bit[2]  |   bit[1]  |   bit[3]  |   bit[9]  |   bit[10] |           |
//------------------------------------------------------------------------------|
//����ֵ��  Shift   |   Z       |   X       |   C       |   V       |   B       |        
//��Ӧλ��  bit[4]  |   bit[11] |   bit[12] |   bit[13] |   bit[14] |   bit[15] |       
//------------------------------------------------------------------------------|
//����ֵ��  Ctrl    |           |           |           |           |           |
//��Ӧλ��  bit[5]  |           |           |           |           |           |
//------------------------------------------------------------------------------|


#define KEY_VALUE_W              KeyValue[0]         //�����Ӧ����ֵ��״̬��1��ʾ�ð������� 0δ����
#define KEY_VALUE_S              KeyValue[1]
#define KEY_VALUE_A              KeyValue[2]
#define KEY_VALUE_D              KeyValue[3]

#define KEY_VALUE_SHIFT          KeyValue[4]
#define KEY_VALUE_CTRL           KeyValue[5]

#define KEY_VALUE_Q              KeyValue[6]
#define KEY_VALUE_E              KeyValue[7]
#define KEY_VALUE_R              KeyValue[8] 

#define KEY_VALUE_F              KeyValue[9]
#define KEY_VALUE_G              KeyValue[10]

#define KEY_VALUE_Z              KeyValue[11]
#define KEY_VALUE_X              KeyValue[12]
#define KEY_VALUE_C              KeyValue[13]
#define KEY_VALUE_V              KeyValue[14]
#define KEY_VALUE_B              KeyValue[15]

#define KEY_PRESSED_OFFSET_W            ((uint16_t)1 << 0)
#define KEY_PRESSED_OFFSET_S            ((uint16_t)1 << 1)
#define KEY_PRESSED_OFFSET_A            ((uint16_t)1 << 2)
#define KEY_PRESSED_OFFSET_D            ((uint16_t)1 << 3)
#define KEY_PRESSED_OFFSET_SHIFT        ((uint16_t)1 << 4)
#define KEY_PRESSED_OFFSET_CTRL         ((uint16_t)1 << 5)
#define KEY_PRESSED_OFFSET_Q            ((uint16_t)1 << 6)
#define KEY_PRESSED_OFFSET_E            ((uint16_t)1 << 7)
#define KEY_PRESSED_OFFSET_R            ((uint16_t)1 << 8)
#define KEY_PRESSED_OFFSET_F            ((uint16_t)1 << 9)
#define KEY_PRESSED_OFFSET_G            ((uint16_t)1 << 10)
#define KEY_PRESSED_OFFSET_Z            ((uint16_t)1 << 11)
#define KEY_PRESSED_OFFSET_X            ((uint16_t)1 << 12)
#define KEY_PRESSED_OFFSET_C            ((uint16_t)1 << 13)
#define KEY_PRESSED_OFFSET_V            ((uint16_t)1 << 14)
#define KEY_PRESSED_OFFSET_B            ((uint16_t)1 << 15)

/*Driver_KeyMouse Param Class Define*/
///*�������*/
typedef struct
{
    int8_t  movfb;          //�����ƶ�          1����    0���޶���    -1����
    int8_t  movlr;          //ǰ���ƶ�         -1��ǰ    0���޶���     1����
    int8_t  movrt;			//������ת		   -1����	 0���޶���	   1����
	
    int8_t  servo;          //���ָǶ�����־    1����    0����
	int8_t  top;         //С����״̬   1:����   0���ر�
	int8_t  corgi;				//Ť��				1:����   0���ر�
	int8_t  superstate; //����״̬      
	int8_t	fireshoot;		//Ħ���ֿ���		1����	 0����
	int8_t  shootfrq  ;	//�ٶȻ��ٶ�			1������	 0������
	int8_t  shootspeed;		//����				1����	 0����
	int8_t	LspeedHfrq;
	int8_t	prediction;  //Ԥ��					1��ûԤ��  0����Ԥ��

}_KeyMouseFlagStruct;

extern _KeyMouseFlagStruct KeyMouseFlag;//��������Ӧ�Ķ�����־ 
extern uint8_t KeyValue[16];//�����Ӧ����ֵ��״̬

void GetKeyValue(void);
void KeyStatusReset(void);
#endif
