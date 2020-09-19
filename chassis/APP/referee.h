#ifndef __REFEREE_H
#define __REFEREE_H

#include "main.h"

#define    LEN_HEADER    5        //֡ͷ��
#define    LEN_CMDID     2        //�����볤��
#define    LEN_TAIL      2	      //֡βCRC16


//��ʼ�ֽ�,Э��̶�Ϊ0xA5
#define    REFEREE_FRAME_HEADER         (0xA5)

typedef enum 
{
	FRAME_HEADER         = 0,
	CMD_ID               = 5,
	DATA                 = 7,
	
}RefereeFrameOffset;

//5�ֽ�֡ͷ,ƫ��λ��
typedef enum
{
	SOF          = 0,//��ʼλ
	DATA_LENGTH  = 1,//֡�����ݳ���,�����������ȡ���ݳ���
	SEQ          = 3,//�����
	CRC8         = 4,//CRC8
	
}FrameHeaderOffset;

/***************������ID********************/

/* 

	ID: 0x0001  Byte:  3    ����״̬����       			����Ƶ�� 1Hz      
	ID: 0x0002  Byte:  1    �����������         		������������      
	ID: 0x0003  Byte:  2    ���������˴������   		1Hz����  
	ID: 0x0101  Byte:  4    �����¼�����   				�¼��ı����
	ID: 0x0102  Byte:  3    ���ز���վ������ʶ����    	�����ı���� 
	ID: 0X0103  Byte:  2    ���ز���վԤԼ�ӵ�����      �����ӷ��ͣ�10Hz 
	ID: 0X0201  Byte: 15    ������״̬����        		10Hz
	ID: 0X0202  Byte: 14    ʵʱ������������   			50Hz       
	ID: 0x0203  Byte: 16    ������λ������           	10Hz
	ID: 0x0204  Byte:  1    ��������������           	����״̬�ı����
	ID: 0x0205  Byte:  3    ���л���������״̬����      10Hz
	ID: 0x0206  Byte:  1    �˺�״̬����           		�˺���������
	ID: 0x0207  Byte:  6    ʵʱ�������           		�ӵ��������
	ID: 0x0301  Byte:  n    �����˼佻������           	���ͷ���������,10Hz
	
*/


//������ID,�����жϽ��յ���ʲô����
typedef enum
{ 
	ID_game_state       					= 0x0001,//����״̬����
	ID_game_result 	   						= 0x0002,//�����������
	ID_game_robot_HP       				= 0x0003,//���������˴������
	ID_dart_state									= 0x0004,
	
	ID_event_data  								= 0x0101,//�����¼����� 
	ID_supply_projectile_action   = 0x0102,//���ز���վ������ʶ����
	ID_referee_warning						=	0x0104,
	ID_dart_remaining_time				= 0x0105,
	
	ID_game_robot_state    				= 0x0201,//������״̬����
	ID_power_heat_data    				= 0x0202,//ʵʱ������������
	ID_game_robot_pos        			= 0x0203,//������λ������
	ID_buff_musk									= 0x0204,//��������������
	ID_aerial_robot_energy				= 0x0205,//���л���������״̬����
	ID_robot_hurt									= 0x0206,//�˺�״̬����
	ID_shoot_data									= 0x0207,//ʵʱ�������

} CmdID;


//���������ݶγ�,���ݹٷ�Э�������峤��
typedef enum
{
	LEN_game_state       					=  3,	//0x0001
	LEN_game_result       				=  1,	//0x0002
	LEN_game_robot_HP				      = 32,	//0x0003
	LEN_dart_state								=	 3,	//0x0004
	
	LEN_event_data  							=  4,	//0x0101
	LEN_supply_projectile_action  =  4,	//0x0102
	LEN_referee_warning           =  2,	//0x0104
	LEN_dart_remaining_time				=  1,	//0x0105
	
	LEN_game_robot_state    			= 18,	//0x0201
	LEN_power_heat_data   				= 16,	//0x0202
	LEN_game_robot_pos        		= 16,	//0x0203
	LEN_buff_musk        					=  1,	//0x0204
	LEN_aerial_robot_energy       =  3,	//0x0205
	LEN_robot_hurt        				=  1,	//0x0206
	LEN_shoot_data       					=  6,	//0x0207
	
}RefereeDataLength;

/* �Զ���֡ͷ */
typedef __packed struct
{
	uint8_t  SOF;
	uint16_t DataLength;
	uint8_t  Seq;
	uint8_t  CRC8;
	
} xFrameHeader;

/* ID: 0x0001  Byte:  3    ����״̬���� */
typedef __packed struct 
{ 
	uint8_t game_type : 4;
	uint8_t game_progress : 4;
	uint16_t stage_remain_time;
} ext_game_state_t; 


/* ID: 0x0002  Byte:  1    ����������� */
typedef __packed struct 
{ 
	uint8_t winner;
} ext_game_result_t; 


/* ID: 0x0003  Byte:  2    ���������˴������ */
typedef __packed struct 
{ 
	uint16_t red_1_robot_HP;
	uint16_t red_2_robot_HP;
	uint16_t red_3_robot_HP;
	uint16_t red_4_robot_HP;
	uint16_t red_5_robot_HP;
	uint16_t red_7_robot_HP;
	uint16_t red_outpost_HP;
	uint16_t red_base_HP;
	uint16_t blue_1_robot_HP;
	uint16_t blue_2_robot_HP;
	uint16_t blue_3_robot_HP;
	uint16_t blue_4_robot_HP;
	uint16_t blue_5_robot_HP;
	uint16_t blue_7_robot_HP;
	uint16_t blue_outpost_HP;
	uint16_t blue_base_HP;
} ext_game_robot_HP_t; 

/* ID: 0x0004  Byte:  3    ���ڷ���״̬ */
typedef __packed struct
{
uint8_t dart_belong;
uint16_t stage_remaining_time;
} ext_dart_status_t;


/* ID: 0x0101  Byte:  4    �����¼����� */
typedef __packed struct 
{ 
	uint32_t event_type;
} ext_event_data_t; 


/* ID: 0x0102  Byte:  4    ���ز���վ������ʶ���� */
typedef __packed struct 
{ 
	uint8_t supply_projectile_id;
	uint8_t supply_robot_id;
	uint8_t supply_projectile_step;
	uint8_t supply_projectile_num;
} ext_supply_projectile_action_t; 


/* ID: 0X0104  Byte:  2    ���о�����Ϣ */
typedef __packed struct
{
uint8_t level;
uint8_t foul_robot_id;
} ext_referee_warning_t;

/* ID: 0X0105  Byte:  1    ���ڷ���ڵ���ʱ */
typedef __packed struct
{
uint8_t dart_remaining_time;
} ext_dart_remaining_time_t;

/* ID: 0X0201  Byte: 15    ������״̬���� */
typedef __packed struct 
{ 
	uint8_t robot_id;   //������ID��������У�鷢��
	uint8_t robot_level;  //1һ����2������3����
	uint16_t remain_HP;  //������ʣ��Ѫ��
	uint16_t max_HP; //��������Ѫ��
	uint16_t shooter_heat0_cooling_rate;  //������ 17mm �ӵ�������ȴ�ٶ� ��λ /s
	uint16_t shooter_heat0_cooling_limit;   // ������ 17mm �ӵ���������
	uint16_t shooter_heat1_cooling_rate;   
	uint16_t shooter_heat1_cooling_limit;   
	uint8_t shooter_heat0_speed_limit;
	uint8_t shooter_heat1_speed_limit;
	uint8_t max_chassis_power;
	uint8_t mains_power_gimbal_output : 1;  
	uint8_t mains_power_chassis_output : 1;  
	uint8_t mains_power_shooter_output : 1; 
} ext_game_robot_state_t; 


/* ID: 0X0202  Byte: 14    ʵʱ������������ */
typedef __packed struct 
{ 
	uint16_t chassis_volt;   
	uint16_t chassis_current;    
	float chassis_power;   //˲ʱ���� 
	uint16_t chassis_power_buffer;//60������������
	uint16_t shooter_heat0;//17mm
	uint16_t shooter_heat1;  
} ext_power_heat_data_t; 


/* ID: 0x0203  Byte: 16    ������λ������ */
typedef __packed struct 
{   
	float x;   
	float y;   
	float z;   
	float yaw; 
} ext_game_robot_pos_t; 


/* ID: 0x0204  Byte:  1    �������������� */
typedef __packed struct 
{ 
	uint8_t power_rune_buff; 
} ext_buff_musk_t; 


/* ID: 0x0205  Byte:  3    ���л���������״̬���� */
typedef __packed struct 
{ 
	uint16_t energy_point;
	uint8_t attack_time; 
} aerial_robot_energy_t; 


/* ID: 0x0206  Byte:  1    �˺�״̬���� */
typedef __packed struct 
{ 
	uint8_t armor_id : 4; 
	uint8_t hurt_type : 4; 
} ext_robot_hurt_t; 


/* ID: 0x0207  Byte:  6    ʵʱ������� */
typedef __packed struct 
{ 
	uint8_t bullet_type;   
	uint8_t bullet_freq;   
	float bullet_speed;  
} ext_shoot_data_t; 



int referee_data_solve(uint8_t *ReadFromUsart);
void determine_ID(void);
uint8_t get_robot_id(void);
void get_chassis_power_and_buffer(float *power, float *buffer,uint16_t *powmax);
void get_shoot_heat0_limit_and_heat0(uint16_t *heat0_limit, uint16_t *heat0);
void get_shoot_heat1_limit_and_heat1(uint16_t *heat1_limit, uint16_t *heat1);
void get_shoot_data(uint8_t *bullet_freq,	float *bullet_speed, uint8_t *bullet_speedlimit);

// CRC8
unsigned char Get_CRC8_Check_Sum(unsigned char *pchMessage,unsigned intdwLength,unsigned char ucCRC8);
unsigned int Verify_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);
void Append_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);

// CRC16
uint16_t Get_CRC16_Check_Sum(uint8_t *pchMessage,uint32_t dwLength,uint16_t wCRC);
uint32_t Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);
void Append_CRC16_Check_Sum(uint8_t * pchMessage,uint32_t dwLength);
#endif
