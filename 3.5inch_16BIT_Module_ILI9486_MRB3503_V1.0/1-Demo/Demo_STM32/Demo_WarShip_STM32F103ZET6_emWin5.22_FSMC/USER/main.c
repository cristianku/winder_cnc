#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "ili93xx.h"
#include "usart.h"	 
#include "24cxx.h"
#include "flash.h"
#include "touch.h"
#include "gui.h" 
#include "guidemo.h"
#include "gui_time.h"

extern void Touch_MainTask(void);

 int main(void)
 {	 
	u8 i=0;	
	u8 key=0;   
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
	LCD_Init();	
	KEY_Init();	
  	TP_Init(); 
		
 	POINT_COLOR=RED;//设置字体为红色 
  TIM3_Init(2,36000-1);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);//不知道为什么一定要开crc时钟	
	
	GUI_Init();//初始化GUI 
	
	GUI_DispString("Hello STemWin!");//显示测试  
	delay_ms(500);
	 key=KEY_Scan(0);
 	if(key==KEY_RIGHT)  
	{
		Touch_MainTask();  //调用校准函数
	}
	else
	GUIDEMO_Main();
	while(1)
	{

		i++;
		if(i==20)
		{
			i=0;
			LED0=!LED0;
		}//delay_ms(20);
	}
}








