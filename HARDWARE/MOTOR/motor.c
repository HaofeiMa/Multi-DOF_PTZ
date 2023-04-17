#include "motor.h"
/*GPIO_motornum��GPIOx����ѡ������GPIO_direction����ѡ��������dir��0Ϊ��1Ϊ����kΪ90��ı���*/
// GPIO

void MOTOR_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(Motor_RCC,ENABLE);
	
	//Motor��ʼ��
	GPIO_InitStructure.GPIO_Pin = Motor1_STEP|Motor1_DIR|Motor2_STEP|Motor2_DIR;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Motor_GPIO,&GPIO_InitStructure);	// ��ʼ��GPIOB
	GPIO_ResetBits(Motor_GPIO,Motor1_STEP);			//��ʼ��GPIOB_6����͵�ƽ
	GPIO_ResetBits(Motor_GPIO,Motor1_DIR);			//��ʼ��GPIOB_7����͵�ƽ
	GPIO_ResetBits(Motor_GPIO,Motor2_STEP);			//��ʼ��GPIOB_8����͵�ƽ
	GPIO_ResetBits(Motor_GPIO,Motor2_DIR);			//��ʼ��GPIOB_9����͵�ƽ
}

/*
void motor(unsigned int motornum, unsigned int dir, unsigned int k)
{
    unsigned int i, steps;
    steps = 50*k;

		if(motornum == 1)
		{
			switch(dir)
			{
        case 0 : 
					GPIO_SetBits(Motor_GPIO,Motor1_DIR); break; 
        case 1 : GPIO_ResetBits(Motor_GPIO,Motor1_DIR); break; 
        default : break; 
			}
			for(i = 0;i < steps; i++)
			{
        GPIO_SetBits(Motor_GPIO,Motor1_STEP);
        delay_ms(2);									//����1.3ms
        GPIO_ResetBits(Motor_GPIO,Motor1_STEP);
        delay_ms(2);
			}
		}
		else if(motornum == 2)
		{
			switch(dir)
			{
        case 0 : GPIO_SetBits(Motor_GPIO,Motor2_DIR); break; 
        case 1 : GPIO_ResetBits(Motor_GPIO,Motor2_DIR); break; 
        default : break; 
			}
			for(i = 0;i < steps; i++)
			{
        GPIO_SetBits(Motor_GPIO,Motor2_STEP);
        delay_ms(2);									//����1.3ms
        GPIO_ResetBits(Motor_GPIO,Motor2_STEP);
        delay_ms(2);
			}
		}

		
    delay_ms(20);					//��ʱһ��
}
*/

void motor(unsigned int motor1_dir, unsigned int motor1_step, unsigned int motor2_dir, unsigned int motor2_step)
{
    unsigned int i;

		switch(motor1_dir)
		{
			case 0 : GPIO_SetBits(Motor_GPIO,Motor1_DIR); break; 
			case 1 : GPIO_ResetBits(Motor_GPIO,Motor1_DIR); break; 
			default : break; 
		}
		switch(motor2_dir)
		{
			case 0 : GPIO_SetBits(Motor_GPIO,Motor2_DIR); break; 
			case 1 : GPIO_ResetBits(Motor_GPIO,Motor2_DIR); break; 
			default : break; 
		}
		/*
		GPIO_SetBits(Motor_GPIO,Motor1_STEP);
		GPIO_SetBits(Motor_GPIO,Motor2_STEP);
		delay_ms(2);									//����1.3ms
		GPIO_ResetBits(Motor_GPIO,Motor1_STEP);
		GPIO_ResetBits(Motor_GPIO,Motor2_STEP);
		delay_ms(2);
		*/
		for(i = 0;i < motor1_step || i < motor2_step; i++)
		{
			if(i<motor1_step)
			{
				GPIO_SetBits(Motor_GPIO,Motor1_STEP);
				delay_ms(2);									//����1.3ms
				GPIO_ResetBits(Motor_GPIO,Motor1_STEP);
				delay_ms(2);
			}
			if(i<motor2_step)
			{
				GPIO_SetBits(Motor_GPIO,Motor2_STEP);
				delay_ms(2);									//����1.3ms
				GPIO_ResetBits(Motor_GPIO,Motor2_STEP);
				delay_ms(2);
			}
		}

    //delay_ms(2);					//��ʱһ��
}
