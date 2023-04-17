#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "delay.h"

//PF0-7,12-15

#define Motor_GPIO GPIOF				//PF
#define Motor_RCC RCC_APB2Periph_GPIOF
//第一个步进电机A4988的接线
#define Motor1_STEP	GPIO_Pin_1	//STEP - PF1
#define Motor1_DIR	GPIO_Pin_2	//DIR  - PF2
//第二个步进电机A4988的接线	//PB
#define Motor2_STEP	GPIO_Pin_3	//STEP - PF3
#define Motor2_DIR	GPIO_Pin_4	//DIR  - PF4

void MOTOR_Init(void);
void motor(unsigned int motor1_dir, unsigned int motor1_step, unsigned int motor2_dir, unsigned int motor2_step);



#endif
