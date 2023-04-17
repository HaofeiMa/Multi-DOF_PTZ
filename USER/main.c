#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "mbotLinuxUsart.h"//���ø�ͷ�ļ���ʹ�ã�ͨ��Э���ǰ��
#include "lcd.h"
#include "motor.h"

#define IMAGE_WIDTH		640/2
#define IMAGE_HEIGHT	480/2

//���Է��ͱ���
short testSend1   =1111;
short testSend2   =2222;
short testSend3   =3333;
unsigned char testSend4 = 0x05;

//���Խ��ձ���
int testRece1     =400;
int testRece2     =300;
unsigned char testRece3 = 0x00;


int main(void)
{	
//=======================================��������=====================================================
	u8 dir1;
	u8 dir2;
	u16 step1;
	u16 step2;
//======================================Ӳ����ʼ��====================================================
	delay_init();	    	                        //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����ж����ȼ�����2
	uart_init(115200);	                            //���ڳ�ʼ��Ϊ115200
	LCD_Init();
	MOTOR_Init();				 //��ʼ��A4988����

//=======================================ѭ������=====================================================
	while(1)
	{
		//����Ҫ���͵�ROS�����ݣ��Ӹú���������ǰ�������ݷ�Χ��-32768 - +32767�������ĸ����ݵķ�Χ(0 - 255)
		usartSendData(testSend1,testSend2,testSend3,testSend4);
		LCD_ShowString(40,30,200,20,24,"ME184 Mahaofei");
		LCD_ShowString(30,80,200,20,24,"Center Position");
		//LCD_ShowxNum(20,60,testSend1,4,24,0);
		LCD_ShowString(20,130,200,20,24,"X Rotation:");
		LCD_ShowxNum(20,160,testRece1,4,24,0);
		LCD_ShowString(20,200,200,20,24,"Y Rotation:");
		LCD_ShowxNum(20,230,testRece2,4,24,0);
	 	//LCD_ShowString(20,240,200,20,24,"Receive Data2:");
		//LCD_ShowxNum(20,270,testRece2,4,24,0);
		if(testRece1>IMAGE_WIDTH)
		{
			dir1=1;
			step1=testRece1-IMAGE_WIDTH;
		}
		else
		{
			dir1=0;
			step1=IMAGE_WIDTH-testRece1;
		}
		if(testRece2>IMAGE_HEIGHT)
		{
			dir2=0;
			step2=testRece2-IMAGE_HEIGHT;
		}
		else
		{
			dir2=1;
			step2=IMAGE_HEIGHT-testRece2;
		}
		motor(dir1,step1,dir2,step2);
		//�������ʱ
		delay_ms(13);
	} 
}

//====================================�����жϷ������=================================================
void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
 	 {
		 USART_ClearITPendingBit(USART1,USART_IT_RXNE);//��������жϱ�־λ
		 //��ROS���յ������ݣ���ŵ���������������
		 usartReceiveOneData(&testRece1,&testRece2,&testRece3);
	 }
}
//===========================================END=======================================================
