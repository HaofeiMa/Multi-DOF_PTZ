#include "motor.h"
/*GPIO_motornum和GPIOx用于选择电机，GPIO_direction用于选择电机方向，dir：0为逆1为正，k为90°的倍数*/
// GPIO

void MOTOR_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(Motor_RCC,ENABLE);
	
	//Motor初始化
	GPIO_InitStructure.GPIO_Pin = Motor1_STEP|Motor1_DIR|Motor2_STEP|Motor2_DIR;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Motor_GPIO,&GPIO_InitStructure);	// 初始化GPIOB
	GPIO_ResetBits(Motor_GPIO,Motor1_STEP);			//初始化GPIOB_6输出低电平
	GPIO_ResetBits(Motor_GPIO,Motor1_DIR);			//初始化GPIOB_7输出低电平
	GPIO_ResetBits(Motor_GPIO,Motor2_STEP);			//初始化GPIOB_8输出低电平
	GPIO_ResetBits(Motor_GPIO,Motor2_DIR);			//初始化GPIOB_9输出低电平
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
        delay_ms(2);									//周期1.3ms
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
        delay_ms(2);									//周期1.3ms
        GPIO_ResetBits(Motor_GPIO,Motor2_STEP);
        delay_ms(2);
			}
		}

		
    delay_ms(20);					//延时一会
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
		delay_ms(2);									//周期1.3ms
		GPIO_ResetBits(Motor_GPIO,Motor1_STEP);
		GPIO_ResetBits(Motor_GPIO,Motor2_STEP);
		delay_ms(2);
		*/
		for(i = 0;i < motor1_step || i < motor2_step; i++)
		{
			if(i<motor1_step)
			{
				GPIO_SetBits(Motor_GPIO,Motor1_STEP);
				delay_ms(2);									//周期1.3ms
				GPIO_ResetBits(Motor_GPIO,Motor1_STEP);
				delay_ms(2);
			}
			if(i<motor2_step)
			{
				GPIO_SetBits(Motor_GPIO,Motor2_STEP);
				delay_ms(2);									//周期1.3ms
				GPIO_ResetBits(Motor_GPIO,Motor2_STEP);
				delay_ms(2);
			}
		}

    //delay_ms(2);					//延时一会
}
