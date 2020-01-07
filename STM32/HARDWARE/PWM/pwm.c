#include "pwm.h"
//#include "led.h"
#include "usart.h"
#include "delay.h"
#include "rs485.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ��PWM ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 


//TIM1 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM1_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM1ʱ��ʹ��    
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ�ӣ�ʹ��PA8��TIM1ͨ��1	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1); //GPIOF9����Ϊ��ʱ��1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           //GPIOA8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PA8
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//��ʼ����ʱ��1
	
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);//���жϱ�־λ
	TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_Trigger,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM1_UP_TIM10_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; //�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//��ʼ��TIM1 Channel1 PWMģʽ	 
	TIM_SelectOnePulseMode(TIM1,TIM_OPMode_Single);//������ģʽ��ÿ�θ����Զ��������
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OCInitStructure.TIM_Pulse = 400;//ռ�ձ�20%
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1OC1
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);//ʹ��TIM1PWM���

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPEʹ�� 
	
	//TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1 
										  
}  



//TIM8 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM8_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  	//TIM8ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//ʹ��PORTEʱ�ӣ�ʹ��PC6��TIM8ͨ��1	
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8); //GPIOC6����Ϊ��ʱ��14
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOC6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);//��ʼ����ʱ��8
	
	TIM_ClearFlag(TIM8, TIM_FLAG_Update);//���жϱ�־λ
	TIM_ITConfig(TIM8,TIM_IT_Update|TIM_IT_Trigger,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM8_UP_TIM13_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02; //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//��ʼ��TIM8 Channel1 PWMģʽ	 
	TIM_SelectOnePulseMode(TIM8,TIM_OPMode_Single);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OCInitStructure.TIM_Pulse = 400;//ռ�ձ�20%
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;//�������PWM�������������
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM8OC1
	
	TIM_CtrlPWMOutputs(TIM8,ENABLE);//ʹ��TIM1PWM���

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //ʹ��TIM8��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM8,ENABLE);//ARPEʹ�� 
	
	//TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM8
 										  
} 

//����ȫ�ֱ���Old_Position���ڼ�¼��һ��ʱ�̵����λ��
u8 Old_x_Position = 0;
u8 Old_y_Position = 0;

u16 x_Pluse_num = 0;
u16 y_Pluse_num = 0;

u8 x_completeFlag = 0;
u8 y_completeFlag = 0;

//��Ļ������������ƾ�ͷ��������x��y��completeflag��Ϊ1ʱ����

void touch()
{
	 if((x_completeFlag==1)&(y_completeFlag==1)&(Old_x_Position==0)&(Old_y_Position==0))//�����λʱ�����
	 {
	   x_completeFlag = 0;	 
	   y_completeFlag = 0;
		 
		 GPIO_SetBits(GPIOG,GPIO_Pin_8);
		 while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
		 USART_SendData(USART2,0xFF);
		 while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //�ȴ����ͽ���
		 GPIO_ResetBits(GPIOG,GPIO_Pin_8);
	 }
	 
   if((x_completeFlag==1)&(y_completeFlag==1)&((Old_x_Position!=0)|(Old_y_Position!=0)))//��xy�����ת��ָ��λ��ʱ����������������PA4��5����
	 {
	   GPIO_SetBits(GPIOA,GPIO_Pin_5);//��ת�ų�
     GPIO_ResetBits(GPIOA,GPIO_Pin_4);		 
	 	 
	   delay_ms(750);
	   GPIO_SetBits(GPIOA,GPIO_Pin_4);//��ת�ջ�
     GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	   delay_ms(750);
	   GPIO_ResetBits(GPIOA,GPIO_Pin_4);	

     x_completeFlag = 0;	 
	   y_completeFlag = 0;
		 
		 GPIO_SetBits(GPIOG,GPIO_Pin_8);
		 while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
		 USART_SendData(USART2,0xFF);
		 while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //�ȴ����ͽ���
		 GPIO_ResetBits(GPIOG,GPIO_Pin_8);
   }
}
//�ֻ���Ļ122*68mm
//x�������ƺ������������ÿ200������תһȦ��˿���ݾ�4mm
//�ú���һ��������256������
void motor_x(u8 pluse_num)
{	
	TIM_SetCounter(TIM1,0);  //���������
	TIM1->RCR=pluse_num;   //�ı��ظ���������ֵ
	x_Pluse_num-=(pluse_num+1);
  TIM_Cmd(TIM1, ENABLE);   //ʹ��TIM1
}


//y�������ƺ������������ͬ��
void motor_y(u8 pluse_num)
{
  TIM_SetCounter(TIM8,0);  //���������
	TIM8->RCR=pluse_num;   //�ı��ظ���������ֵ
	y_Pluse_num-=(pluse_num+1);
  TIM_Cmd(TIM8, ENABLE);   //ʹ��TIM8
}

#define sub  8;  //����ϸ��ֵ

//x����������PB0���ƣ�y����������PB1����
//����������Ӧ�ĵ����Ҫ����������
void motor_x_reversecontrol(u8 New_Postion)
{
if (New_Postion<Old_x_Position) 
 {
	GPIO_SetBits(GPIOB,GPIO_Pin_0);                           //��תʱ��һ��������Ϊ��������
	x_Pluse_num = 50+244*(Old_x_Position-New_Postion)/4*sub;  //244��iphone6sp��Ļ�߶ȵ�2������λ����
	Old_x_Position =  New_Postion;
 }
else
 {
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	x_Pluse_num = 244*(New_Postion-Old_x_Position)/4*sub;
	Old_x_Position =  New_Postion;
 }
}

void motor_y_reversecontrol(u8 New_Postion)
{
if (New_Postion<Old_y_Position) 
 {
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
	y_Pluse_num = 40+136*(Old_y_Position-New_Postion)/4*sub;   //136��iphone6sp��Ļ��ȵ�2������λ����
	Old_y_Position =  New_Postion;
 }
else
 {
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	y_Pluse_num = 136*(New_Postion-Old_y_Position)/4*sub;
	Old_y_Position =  New_Postion;
 }
}



void move_xy(u8 x_position, u8 y_position)
{
			motor_x_reversecontrol(x_position);
			motor_y_reversecontrol(y_position);
	
	    x_completeFlag = 0;	 
	    y_completeFlag = 0;
	
	    if((x_position==0)&(y_position==0))    //��λʱ����800�����壬��֤��ȫ�ص�ԭ��
			{
				  GPIO_SetBits(GPIOB,GPIO_Pin_0);
				  GPIO_SetBits(GPIOB,GPIO_Pin_1);
			    x_Pluse_num+=850;
				  y_Pluse_num+=800;
			}
	
	    delay_ms(50);

		if(x_Pluse_num>0)
		{
			TIM_SetAutoreload(TIM1,1200-1);//����Ƶ��800Hz��֮�����ж����Ϊ2kHZ
			
		  if(x_Pluse_num<=30)            //��30��������Ϊ��������
			{
        motor_x(x_Pluse_num-1);
			}
			else
			{
			  motor_x(29);
			}
		}
			
		if(y_Pluse_num>0)
		{
			TIM_SetAutoreload(TIM8,1200-1);
			
		  if(y_Pluse_num<=30)
			{
        motor_y(y_Pluse_num-1);
			}
			else
			{
			  motor_y(29);
			}
		}
		
		if(x_Pluse_num==0)//�������Ҫ���ת������ɱ�־λֱ����1
			x_completeFlag=1;
		
		if(y_Pluse_num==0)
			y_completeFlag=1;


}


//�жϺ���:�����ת����Ӧλ��ʱ����PWM����ȫ����󣩹رն�ʱ��
void TIM1_UP_TIM10_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)//���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);//���TIMx���жϴ�����λ:TIM �ж�Դ 
    TIM_Cmd(TIM1, DISABLE);
		
		
			if(x_Pluse_num>0)
		{
			TIM_SetAutoreload(TIM1,450-1);
		  if(x_Pluse_num<=256)
			{
        motor_x(x_Pluse_num-1);
			}
			else
			{
			  motor_x(255);
			}
		}
		
		if(x_Pluse_num==0)
		  x_completeFlag = 1;	
  }
}

void TIM8_UP_TIM13_IRQHandler()
{
	if (TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET)//���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM8, TIM_IT_Update);//���TIMx���жϴ�����λ:TIM �ж�Դ 
    TIM_Cmd(TIM8, DISABLE);
		
		
			if(y_Pluse_num>0)
		{
			TIM_SetAutoreload(TIM8,500-1);
		  if(y_Pluse_num<=256)
			{
        motor_y(y_Pluse_num-1);
			}
			else
			{
			  motor_y(255);
			}
		}
		if(y_Pluse_num==0)
		  y_completeFlag = 1;	
  }
}

