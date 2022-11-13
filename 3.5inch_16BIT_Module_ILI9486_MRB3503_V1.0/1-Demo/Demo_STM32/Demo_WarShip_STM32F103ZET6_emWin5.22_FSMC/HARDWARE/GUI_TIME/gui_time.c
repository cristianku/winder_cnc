#include "led.h"
#include "gui_time.h"
#include "gui.h"

extern volatile int OS_TimeMS;
void TIM3_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM3_InitStructure;
  NVIC_InitTypeDef  NVIC_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
  TIM3_InitStructure.TIM_Prescaler=psc;
  TIM3_InitStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM3_InitStructure.TIM_Period=arr;
  TIM3_InitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM3,&TIM3_InitStructure);
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  TIM_Cmd(TIM3,ENABLE);
}
//void GUI_TOUCH_Exec(void);

void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
	   TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	   OS_TimeMS++;
	   if(OS_TimeMS%20==0)
	   {
	    GUI_TOUCH_Exec();
			LED1=!LED1;
	   }
	}
}   
