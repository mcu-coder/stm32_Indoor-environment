#include "sys.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "delay.h"
#include "gpio.h"
#include "key.h"
#include "oled.h"
#include "usart.h"
#include "adc.h"
#include "ds18b20.h"
#include "timer.h"
#include "motor_dianji.h"


/**********************************
变量定义
**********************************/
uint8_t key_num = 0;									//按键扫描标志位	
uint8_t flag_display = 0;							//显示界面标志位
uint32_t time_num = 0;								//10ms计时
uint32_t light_value = 0;							//光照数值
uint32_t light_min = 40;							//光照数值
u16  temp_value = 0;									//温度值
u16  temp_min = 15;										//温度最小值
u16  temp_zj = 25;										//温度中间值
u16  temp_max = 30;										//温度最大值
extern uint8_t usart1_buf[256];				//串口1接收数组
char display_buf[32];									//显示缓存区
_Bool flag_mode = 0;									//模式标志位
uint8_t flag_motor_speed = 0;					//电机速度标志位
uint32_t speed_value = 0;							//速度值

_Bool flag_mode_r = 0;                //模式标志位
/**********************************
函数声明
**********************************/
void Key_function(void);							//按键函数
void Monitor_function(void);					//监测函数
void Display_function(void);					//显示函数
void Manage_function(void);						//处理函数


/****
*******	主函数 
*****/
int main(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //配置中断优先分组
	Delay_Init();	    	 								//延时初始化	  
	Gpio_Init();		  									//IO初始化
	Key_Init();		  										//按键初始化
	Oled_Init();		  									//OLED初始化
	Oled_Clear_All();										//清屏
	 
	Delay_ms(1000);

	
	while(1)
	{
		Key_function();										//按键函数
		Monitor_function();								//监测函数
		Display_function();								//显示函数
		Manage_function();								//处理函数

		time_num++;												//计时变量+1
		Delay_ms(10);
		if(time_num %10 == 0)
			LED_SYS = ~LED_SYS;
		if(time_num >= 5000)
		{
			time_num = 0;
		}
	}
}

/****
*******按键函数
*****/
void Key_function(void)
{
	key_num = Chiclet_Keyboard_Scan(0);		//按键扫描
	if(key_num != 0)											//有按键按下
	{
		switch(key_num)
		{
			case 1:								            //按键1，切换设置界面
				flag_display++;
				if(flag_display >= 5)
					flag_display = 0;
				
				Oled_Clear_All();					      //清屏
			break;
 

			default:
				
			break;
		}
	}
}

/****
*******监测函数
*****/
void Monitor_function(void)
{
	if(flag_display == 0)									//测量界面
	{
		if(time_num % 10 == 0)							//获取数据
		{
			light_value = 99-30*(Get_Adc_Average(0,3)*3.3/4096.0);		//获取光照强度
			temp_value = DS18B20_Get_Temp();
		}
		   
		if(flag_mode_r == 0)
		{
			if(IRED == 0)
			{
				flag_mode =0;
			}
			else
			{
				flag_mode = 1; 
				RELAY_JR = 0;
				RELAY_ZL = 0;
				RELAY_ZM = 0;
				flag_motor_speed = 0; 
			}
		}

	}
}

/****
*******显示函数
*****/
void Display_function(void)
{
	switch(flag_display)									//根据不同的显示模式标志位，显示不同的界面
	{
		case 0:									      			//界面0：
			Oled_ShowCHinese(1, 0, "温度：");
			sprintf(display_buf,"%d.%dC  ",temp_value/10,temp_value%10);				//显示温度的值
			Oled_ShowString(1, 6, display_buf);
		 
			
			Oled_ShowCHinese(4, 0, "蓝牙模式："); 
			
			if(flag_mode_r == 1)
				Oled_ShowCHinese(4, 5, "开启");
			else
				Oled_ShowCHinese(4, 5, "关闭");
		break;
		 
		
		default:
			
		break;
	}
}

/****
*******处理函数
*****/
void Manage_function(void)
{
	if(flag_mode == 0 && flag_mode_r == 0)
	{
		if(flag_display == 0)                  //测量界面
		{
			if(temp_value > temp_max*10)
			{
				RELAY_ZL = 1;
				RELAY_JR = 0;
				flag_motor_speed = 0;
			} 
			else
			{
				flag_motor_speed = 0;
				RELAY_ZL = 0;
				RELAY_JR = 1;
			}
			
		 
		}
		else													         //设置界面
		{
			RELAY_ZM = 0;
			RELAY_JR = 0;
			RELAY_ZL = 0;
			flag_motor_speed = 0;
		}
	} 
	TIM_SetCompare1(MOTOR_DIANJI_TIM,speed_value);
	
}

