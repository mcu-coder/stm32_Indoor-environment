#ifndef __GPIO_H
#define __GPIO_H


/**********************************
包含头文件
**********************************/
#include "sys.h"


/**********************************
重定义关键词
**********************************/
#define LEDS_GPIO_PORT                GPIOC        	//最小系统LED
#define LEDS_GPIO_PIN                 GPIO_Pin_13
#define LED_SYS                       PCout(13)

#define IRED_GPIO_PORT                GPIOB					//红外触发引脚
#define IRED_GPIO_PIN                 GPIO_Pin_12
#define IRED                          PBin(12)

#define RELAY_JR_GPIO_CLK             RCC_APB2Periph_GPIOA				//加热继电器引脚
#define RELAY_JR_PORT                 GPIOA
#define RELAY_JR_PIN                  GPIO_Pin_7
#define RELAY_JR 											PAout(7)

#define RELAY_ZL_GPIO_CLK             RCC_APB2Periph_GPIOB				//制冷继电器引脚
#define RELAY_ZL_PORT                 GPIOB
#define RELAY_ZL_PIN                  GPIO_Pin_0
#define RELAY_ZL 											PBout(0)

#define RELAY_ZM_GPIO_CLK             RCC_APB2Periph_GPIOB				//照明继电器引脚
#define RELAY_ZM_PORT                 GPIOB
#define RELAY_ZM_PIN                  GPIO_Pin_1
#define RELAY_ZM 											PBout(1)


#define MOTOR_IN0_GPIO_CLK            RCC_APB2Periph_GPIOA				//电机0引脚		
#define MOTOR_IN0_PORT                GPIOA
#define MOTOR_IN0_PIN                 GPIO_Pin_5
#define MOTOR_IN0											PAout(5)

#define MOTOR_IN1_GPIO_CLK            RCC_APB2Periph_GPIOA				//电机1引脚
#define MOTOR_IN1_PORT                GPIOA
#define MOTOR_IN1_PIN                 GPIO_Pin_6
#define MOTOR_IN1											PAout(6)
/**********************************
函数声明
**********************************/
void Gpio_Init(void);																//GPIO初始化


#endif

