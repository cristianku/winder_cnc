//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STC12C5A60S2,晶振30M  单片机工作电压3.3V
//QDtech-LCD液晶驱动 for C51
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtft.com
//淘宝网站：http://qdtech.taobao.com
//wiki技术网站：http://www.lcdwiki.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//技术支持QQ:3002773612  3002778157
//技术交流QQ群:324828016
//创建日期:2018/7/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
//********************************************************************************
//=========================================电源接线================================================//
//VDD接DC 5V或3.3V电源
//GND接地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为16位并口
//液晶屏模块             C51单片机
// DB0~DB7       接       P00~P07        //数据低8位（8位模式：DB0~DB7接P00~P07）
// DB8~DB15      接       P20~P27        //数据高8位
//=======================================液晶屏控制线接线==========================================//
//液晶屏模块             C51单片机
//   CS          接        P13           //片选控制信号
//   RST         接        P33           //复位信号
//   RS          接        P12           //数据/命令选择控制信号
//   WR          接        P11           //写控制信号
//   RD          接        P10           //读控制信号
//   BL          接        P32           //背光控制信号
//=========================================触摸屏接线=========================================//
//不使用触摸或者模块本身不带触摸，则可不连接
//触摸屏使用的数据总线类型为SPI
//触摸屏模块             C51单片机
//  CLK          接        P36           //触摸屏SPI时钟信号
//  T_CS         接        P37           //触摸屏片选控制信号
//  MISO         接        P35           //触摸屏SPI写信号
//  MOSI         接        P34           //触摸屏SPI读信号
//  PEN          接        P40           //触摸屏响应检查信号，如单片机无P4组，请自行更改其他可用IO并修改代码定义
//**************************************************************************************************/			
#include "sys.h"
#include "lcd.h"
#include "gui.h"
#include "test.h"
#include "touch.h"

//主函数
void main(void)
{ 

	//设置STC_12LE5A60S2单片机的P3.2为推挽输出，用于控制背光亮灭
	//其他普通C51单片机无此配置请屏蔽下面这条语句
	P3M1 &= ~(1<<2),P3M0 |=  (1<<2); 

	//液晶屏初始化
	LCD_Init();

	//循环进行各项测试	
	while(1)
	{
		main_test(); 		//测试主界面
		Test_Read();     //读ID和颜色值测试
		Test_Color();  		//简单刷屏填充测试
		Test_FillRec();		//GUI矩形绘图测试
		Test_Circle(); 		//GUI画圆测试
		Test_Triangle();   //GUI三角形填充测试
		English_Font_test();//英文字体示例测试
		Chinese_Font_test();//中文字体示例测试
		Pic_test();			//图片显示示例测试
		Rotate_Test();  //屏幕旋转测试
	//不使用触摸或者模块本身不带触摸，请屏蔽下面触摸屏测试	
		Touch_Test();		//触摸屏手写测试
	//需要触摸校准时，请将触摸手写测试屏蔽，将下面触摸校准测试项打开
	//	Touch_Adjust();  //触摸校准
	}   
}
