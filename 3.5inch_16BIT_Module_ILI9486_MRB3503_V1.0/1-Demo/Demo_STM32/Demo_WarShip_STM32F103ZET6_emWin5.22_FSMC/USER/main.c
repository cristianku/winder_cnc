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
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();	
	KEY_Init();	
  	TP_Init(); 
		
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
  TIM3_Init(2,36000-1);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);//��֪��Ϊʲôһ��Ҫ��crcʱ��	
	
	GUI_Init();//��ʼ��GUI 
	
	GUI_DispString("Hello STemWin!");//��ʾ����  
	delay_ms(500);
	 key=KEY_Scan(0);
 	if(key==KEY_RIGHT)  
	{
		Touch_MainTask();  //����У׼����
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








