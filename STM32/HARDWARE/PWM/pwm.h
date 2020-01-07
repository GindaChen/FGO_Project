#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/6/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

void TIM1_PWM_Init(u32 arr,u32 psc);
void TIM8_PWM_Init(u32 arr,u32 psc);

void motor_x(u8 pluse_num);
void motor_y(u8 pluse_num);
void touch(void);

void motor_x_reversecontrol(u8 New_Postion);
void motor_y_reversecontrol(u8 New_Postion);

void move_xy(u8 x_position, u8 y_position);

//extern u16 x_Pluse_num;
//extern u16 y_Pluse_num;
//extern u8 x_completeFlag;
//extern u8 y_completeFlag;
#endif
