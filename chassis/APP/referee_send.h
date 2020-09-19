#ifndef REFEREE_SEND_H
#define REFEREE_SEND_H

#include "main.h"
#include "referee.h"

/* 
	ѧ�������˼�ͨ�� cmd_id 0x0301������ ID:0x0200~0x02FF
	�������� �����˼�ͨ�ţ�0x0301��
	����Ƶ�ʣ����� 10Hz  

	�ֽ�ƫ���� 	��С 	˵�� 			��ע 
	0 			2 		���ݵ����� ID 	0x0200~0x02FF 
										���������� ID ��ѡȡ������ ID �����ɲ������Զ��� 
	
	2 			2 		�����ߵ� ID 	��ҪУ�鷢���ߵ� ID ��ȷ�ԣ� 
	
	4 			2 		�����ߵ� ID 	��ҪУ������ߵ� ID ��ȷ�ԣ�
										���粻�ܷ��͵��жԻ����˵�ID 
	
	6 			n 		���ݶ� 			n ��ҪС�� 113 

*/
typedef __packed struct 
{ 
	uint8_t data[2]; //���ݶ�,n��ҪС��113
} robot_interactive_data_t;

typedef __packed struct
{ 
	uint8_t graphic_name[3]; //ͼ����,��ɾ�����޸ĵȲ����У���Ϊ�ͻ��˵�������
	uint32_t operate_tpye:3; //ͼ�β�����0���ղ�����1�����ӣ�2���޸ģ�3��ɾ����
	uint32_t graphic_tpye:3; //ͼ�����ͣ�0��ֱ�ߣ�1�����Σ�2����Բ��3����Բ��4��Բ����
	uint32_t layer:4; //ͼ������0~9
	uint32_t color:4; //��ɫ��0��������ɫ��1����ɫ��2����ɫ��3����ɫ��4���Ϻ�ɫ��5����ɫ��6����ɫ��7����ɫ��8����ɫ��
	uint32_t start_angle:9; //����ʼ�Ƕȣ���λ���㣬��Χ[0,360]��
	uint32_t end_angle:9; //��ֹ�Ƕȣ���λ���㣬��Χ[0,360]��
	uint32_t width:10; //�߿�
	uint32_t start_x:11; //���x���ꣻ
	uint32_t start_y:11; //���y���ꡣ
	uint32_t radius:10; //�����С���߰뾶��
	uint32_t end_x:11; //�յ�x���ꣻ
	uint32_t end_y:11; //�յ�y���ꡣ
} graphic_data_struct_t;


/* �ͻ���ɾ��ͼ��  �����˼�ͨ�ţ� 0x0301 ����id��0x0100*/
typedef __packed struct
{ 
	uint8_t operate_tpye; 
	uint8_t layer; 
} graphic_delete_t;


/*�ͻ��˻���һ��ͼ�� �����˼�ͨ�ţ� 0x0301 ����id��0x0101*/
typedef __packed struct
{
	graphic_data_struct_t grapic_data_struct;
}ext_client_custom_graphic_single_t;

/*�ͻ��˻��ƶ���ͼ�� �����˼�ͨ�ţ� 0x0301 ����id��0x0102*/
typedef __packed struct
{
	graphic_data_struct_t grapic_data_struct[2];
}ext_client_custom_graphic_double_t;

/*�ͻ��˻������ͼ�� �����˼�ͨ�ţ� 0x0301 ����id��0x0103*/
typedef __packed struct
{
	graphic_data_struct_t grapic_data_struct[5];
}ext_client_custom_graphic_five_t;

/*�ͻ��˻����߸�ͼ�� �����˼�ͨ�ţ� 0x0301 ����id��0x0104*/
typedef __packed struct
{
	graphic_data_struct_t grapic_data_struct[7];
}ext_client_custom_graphic_seven_t;

/*�ͻ��˻����ַ� �����˼�ͨ�ţ� 0x0301 ����id�� 0x0110*/
typedef __packed struct
{
graphic_data_struct_t grapic_data_struct;
uint8_t data[30];
} ext_client_custom_character_t;

typedef __packed struct //0x0301
{//������֮�����ݽ�����Ϣ
/*	���ݶε� ����ID����ע����cmd_id���֣�
	0x0200~0x02FF	6+n	���������˼�ͨ��
	0x0100	6+2		�ͻ���ɾ��ͼ��
	0x0101	6+15	�ͻ��˻���һ��ͼ��
	0x0102	6+30	�ͻ��˻��ƶ���ͼ��
	0x0103	6+75	�ͻ��˻������ͼ��
	0x0104	6+105	�ͻ��˻����߸�ͼ��
	0x0110	6+45	�ͻ��˻����ַ�ͼ��
*/
	__packed struct
	{
	  uint8_t SOF;
	  uint16_t data_length;
	  uint8_t seq;
	  uint8_t CRC8;
	} frame_header_struct_t;
	
	uint16_t cmd_id;
	
	uint16_t data_cmd_id; //���ݶε�����ID
	uint16_t sender_ID; //�����ߵ�ID
	uint16_t receiver_ID; //�����ߵ�ID
	graphic_data_struct_t grap[7];//���ݶΣ����113
	
	uint16_t crc16;
} graphic_add_t;


void UI_init(void);
void UI_show(void);














#endif
