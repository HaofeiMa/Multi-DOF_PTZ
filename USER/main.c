#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "mbotLinuxUsart.h"//引用该头文件是使用，通信协议的前提
#include "lcd.h"
#include "motor.h"

#define IMAGE_WIDTH		640/2
#define IMAGE_HEIGHT	480/2

//测试发送变量
short testSend1   =1111;
short testSend2   =2222;
short testSend3   =3333;
unsigned char testSend4 = 0x05;

//测试接收变量
int testRece1     =400;
int testRece2     =300;
unsigned char testRece3 = 0x00;


int main(void)
{	
//=======================================变量定义=====================================================
	u8 dir1;
	u8 dir2;
	u16 step1;
	u16 step2;
//======================================硬件初始化====================================================
	delay_init();	    	                        //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级分组2
	uart_init(115200);	                            //串口初始化为115200
	LCD_Init();
	MOTOR_Init();				 //初始化A4988驱动

//=======================================循环程序=====================================================
	while(1)
	{
		//将需要发送到ROS的数据，从该函数发出，前三个数据范围（-32768 - +32767），第四个数据的范围(0 - 255)
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
		//必须的延时
		delay_ms(13);
	} 
}

//====================================串口中断服务程序=================================================
void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
 	 {
		 USART_ClearITPendingBit(USART1,USART_IT_RXNE);//首先清除中断标志位
		 //从ROS接收到的数据，存放到下面三个变量中
		 usartReceiveOneData(&testRece1,&testRece2,&testRece3);
	 }
}
//===========================================END=======================================================
