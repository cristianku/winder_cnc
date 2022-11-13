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
#ifndef __FONT_H
#define __FONT_H 	
//取模方式：
//字体:Default
//逐行式，逆向（低位在前） 
//常用ASCII表
//偏移量32
//ASCII字符集
//偏移量32
//大小:12*6
code unsigned char asc2_1206[95][12]={
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/
{0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x04,0x00,0x00},/*"!",1*/
{0x00,0x14,0x0A,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*""",2*/
{0x00,0x00,0x14,0x14,0x3F,0x14,0x0A,0x3F,0x0A,0x0A,0x00,0x00},/*"#",3*/
{0x00,0x04,0x1E,0x15,0x05,0x06,0x0C,0x14,0x15,0x0F,0x04,0x00},/*"$",4*/
{0x00,0x00,0x12,0x15,0x0D,0x0A,0x14,0x2C,0x2A,0x12,0x00,0x00},/*"%",5*/
{0x00,0x00,0x04,0x0A,0x0A,0x1E,0x15,0x15,0x09,0x36,0x00,0x00},/*"&",6*/
{0x00,0x02,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",7*/
{0x00,0x20,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x20,0x00},/*"(",8*/
{0x00,0x02,0x04,0x08,0x08,0x08,0x08,0x08,0x08,0x04,0x02,0x00},/*")",9*/
{0x00,0x00,0x00,0x04,0x15,0x0E,0x0E,0x15,0x04,0x00,0x00,0x00},/*"*",10*/
{0x00,0x00,0x04,0x04,0x04,0x1F,0x04,0x04,0x04,0x00,0x00,0x00},/*"+",11*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x01},/*",",12*/
{0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00},/*"-",13*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00},/*".",14*/
{0x00,0x10,0x08,0x08,0x08,0x04,0x04,0x02,0x02,0x02,0x01,0x00},/*"/",15*/
{0x00,0x00,0x0E,0x11,0x11,0x11,0x11,0x11,0x11,0x0E,0x00,0x00},/*"0",16*/
{0x00,0x00,0x04,0x06,0x04,0x04,0x04,0x04,0x04,0x0E,0x00,0x00},/*"1",17*/
{0x00,0x00,0x0E,0x11,0x11,0x08,0x04,0x02,0x01,0x1F,0x00,0x00},/*"2",18*/
{0x00,0x00,0x0E,0x11,0x10,0x0C,0x10,0x10,0x11,0x0E,0x00,0x00},/*"3",19*/
{0x00,0x00,0x08,0x0C,0x0A,0x0A,0x09,0x1E,0x08,0x18,0x00,0x00},/*"4",20*/
{0x00,0x00,0x1F,0x01,0x01,0x0F,0x10,0x10,0x11,0x0E,0x00,0x00},/*"5",21*/
{0x00,0x00,0x0E,0x09,0x01,0x0F,0x11,0x11,0x11,0x0E,0x00,0x00},/*"6",22*/
{0x00,0x00,0x1F,0x09,0x08,0x04,0x04,0x04,0x04,0x04,0x00,0x00},/*"7",23*/
{0x00,0x00,0x0E,0x11,0x11,0x0E,0x11,0x11,0x11,0x0E,0x00,0x00},/*"8",24*/
{0x00,0x00,0x0E,0x11,0x11,0x11,0x1E,0x10,0x12,0x0E,0x00,0x00},/*"9",25*/
{0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x04,0x00,0x00},/*":",26*/
{0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x04,0x00},/*";",27*/
{0x00,0x20,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x20,0x00,0x00},/*"<",28*/
{0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x1F,0x00,0x00,0x00,0x00},/*"=",29*/
{0x00,0x02,0x04,0x08,0x10,0x20,0x10,0x08,0x04,0x02,0x00,0x00},/*">",30*/
{0x00,0x00,0x0E,0x11,0x11,0x08,0x04,0x04,0x00,0x04,0x00,0x00},/*"?",31*/
{0x00,0x00,0x0E,0x11,0x19,0x15,0x15,0x1D,0x01,0x1E,0x00,0x00},/*"@",32*/
{0x00,0x00,0x04,0x04,0x0C,0x0A,0x0A,0x1E,0x12,0x33,0x00,0x00},/*"A",33*/
{0x00,0x00,0x0F,0x12,0x12,0x0E,0x12,0x12,0x12,0x0F,0x00,0x00},/*"B",34*/
{0x00,0x00,0x1E,0x11,0x01,0x01,0x01,0x01,0x11,0x0E,0x00,0x00},/*"C",35*/
{0x00,0x00,0x0F,0x12,0x12,0x12,0x12,0x12,0x12,0x0F,0x00,0x00},/*"D",36*/
{0x00,0x00,0x1F,0x12,0x0A,0x0E,0x0A,0x02,0x12,0x1F,0x00,0x00},/*"E",37*/
{0x00,0x00,0x1F,0x12,0x0A,0x0E,0x0A,0x02,0x02,0x07,0x00,0x00},/*"F",38*/
{0x00,0x00,0x1C,0x12,0x01,0x01,0x39,0x11,0x12,0x0C,0x00,0x00},/*"G",39*/
{0x00,0x00,0x33,0x12,0x12,0x1E,0x12,0x12,0x12,0x33,0x00,0x00},/*"H",40*/
{0x00,0x00,0x1F,0x04,0x04,0x04,0x04,0x04,0x04,0x1F,0x00,0x00},/*"I",41*/
{0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x09,0x07,0x00},/*"J",42*/
{0x00,0x00,0x37,0x12,0x0A,0x06,0x0A,0x0A,0x12,0x37,0x00,0x00},/*"K",43*/
{0x00,0x00,0x07,0x02,0x02,0x02,0x02,0x02,0x22,0x3F,0x00,0x00},/*"L",44*/
{0x00,0x00,0x1B,0x1B,0x1B,0x1B,0x15,0x15,0x15,0x15,0x00,0x00},/*"M",45*/
{0x00,0x00,0x3B,0x12,0x16,0x16,0x1A,0x1A,0x12,0x17,0x00,0x00},/*"N",46*/
{0x00,0x00,0x0E,0x11,0x11,0x11,0x11,0x11,0x11,0x0E,0x00,0x00},/*"O",47*/
{0x00,0x00,0x0F,0x12,0x12,0x0E,0x02,0x02,0x02,0x07,0x00,0x00},/*"P",48*/
{0x00,0x00,0x0E,0x11,0x11,0x11,0x11,0x17,0x19,0x0E,0x18,0x00},/*"Q",49*/
{0x00,0x00,0x0F,0x12,0x12,0x0E,0x0A,0x12,0x12,0x37,0x00,0x00},/*"R",50*/
{0x00,0x00,0x1E,0x11,0x01,0x06,0x08,0x10,0x11,0x0F,0x00,0x00},/*"S",51*/
{0x00,0x00,0x1F,0x15,0x04,0x04,0x04,0x04,0x04,0x0E,0x00,0x00},/*"T",52*/
{0x00,0x00,0x33,0x12,0x12,0x12,0x12,0x12,0x12,0x0C,0x00,0x00},/*"U",53*/
{0x00,0x00,0x33,0x12,0x12,0x0A,0x0A,0x0C,0x04,0x04,0x00,0x00},/*"V",54*/
{0x00,0x00,0x15,0x15,0x15,0x0E,0x0A,0x0A,0x0A,0x0A,0x00,0x00},/*"W",55*/
{0x00,0x00,0x1B,0x0A,0x0A,0x04,0x04,0x0A,0x0A,0x1B,0x00,0x00},/*"X",56*/
{0x00,0x00,0x1B,0x0A,0x0A,0x04,0x04,0x04,0x04,0x0E,0x00,0x00},/*"Y",57*/
{0x00,0x00,0x1F,0x09,0x08,0x04,0x04,0x02,0x12,0x1F,0x00,0x00},/*"Z",58*/
{0x00,0x1C,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x1C,0x00},/*"[",59*/
{0x00,0x02,0x02,0x02,0x04,0x04,0x08,0x08,0x08,0x10,0x00,0x00},/*"\",60*/
{0x00,0x0E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0E,0x00},/*"]",61*/
{0x00,0x04,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"^",62*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F},/*"_",63*/
{0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"`",64*/
{0x00,0x00,0x00,0x00,0x00,0x0C,0x12,0x1C,0x12,0x3C,0x00,0x00},/*"a",65*/
{0x00,0x00,0x03,0x02,0x02,0x0E,0x12,0x12,0x12,0x0E,0x00,0x00},/*"b",66*/
{0x00,0x00,0x00,0x00,0x00,0x1C,0x12,0x02,0x02,0x1C,0x00,0x00},/*"c",67*/
{0x00,0x00,0x18,0x10,0x10,0x1C,0x12,0x12,0x12,0x3C,0x00,0x00},/*"d",68*/
{0x00,0x00,0x00,0x00,0x00,0x0C,0x12,0x1E,0x02,0x1C,0x00,0x00},/*"e",69*/
{0x00,0x00,0x38,0x04,0x04,0x1E,0x04,0x04,0x04,0x1E,0x00,0x00},/*"f",70*/
{0x00,0x00,0x00,0x00,0x00,0x3C,0x12,0x0C,0x02,0x1E,0x22,0x1C},/*"g",71*/
{0x00,0x00,0x03,0x02,0x02,0x0E,0x12,0x12,0x12,0x37,0x00,0x00},/*"h",72*/
{0x00,0x00,0x04,0x00,0x00,0x06,0x04,0x04,0x04,0x0E,0x00,0x00},/*"i",73*/
{0x00,0x00,0x08,0x00,0x00,0x0C,0x08,0x08,0x08,0x08,0x08,0x07},/*"j",74*/
{0x00,0x00,0x03,0x02,0x02,0x3A,0x0A,0x0E,0x12,0x37,0x00,0x00},/*"k",75*/
{0x00,0x00,0x07,0x04,0x04,0x04,0x04,0x04,0x04,0x1F,0x00,0x00},/*"l",76*/
{0x00,0x00,0x00,0x00,0x00,0x0F,0x15,0x15,0x15,0x15,0x00,0x00},/*"m",77*/
{0x00,0x00,0x00,0x00,0x00,0x0F,0x12,0x12,0x12,0x37,0x00,0x00},/*"n",78*/
{0x00,0x00,0x00,0x00,0x00,0x0C,0x12,0x12,0x12,0x0C,0x00,0x00},/*"o",79*/
{0x00,0x00,0x00,0x00,0x00,0x0F,0x12,0x12,0x12,0x0E,0x02,0x07},/*"p",80*/
{0x00,0x00,0x00,0x00,0x00,0x1C,0x12,0x12,0x12,0x1C,0x10,0x38},/*"q",81*/
{0x00,0x00,0x00,0x00,0x00,0x1B,0x06,0x02,0x02,0x07,0x00,0x00},/*"r",82*/
{0x00,0x00,0x00,0x00,0x00,0x1E,0x02,0x0C,0x10,0x1E,0x00,0x00},/*"s",83*/
{0x00,0x00,0x00,0x04,0x04,0x0E,0x04,0x04,0x04,0x18,0x00,0x00},/*"t",84*/
{0x00,0x00,0x00,0x00,0x00,0x1B,0x12,0x12,0x12,0x3C,0x00,0x00},/*"u",85*/
{0x00,0x00,0x00,0x00,0x00,0x37,0x12,0x0A,0x0C,0x04,0x00,0x00},/*"v",86*/
{0x00,0x00,0x00,0x00,0x00,0x15,0x15,0x0E,0x0A,0x0A,0x00,0x00},/*"w",87*/
{0x00,0x00,0x00,0x00,0x00,0x1B,0x0A,0x04,0x0A,0x1B,0x00,0x00},/*"x",88*/
{0x00,0x00,0x00,0x00,0x00,0x37,0x12,0x0A,0x0C,0x04,0x04,0x03},/*"y",89*/
{0x00,0x00,0x00,0x00,0x00,0x1E,0x08,0x04,0x04,0x1E,0x00,0x00},/*"z",90*/
{0x00,0x18,0x08,0x08,0x08,0x04,0x08,0x08,0x08,0x08,0x18,0x00},/*"{",91*/
{0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08},/*"|",92*/
{0x00,0x06,0x04,0x04,0x04,0x08,0x04,0x04,0x04,0x04,0x06,0x00},/*"}",93*/
{0x02,0x25,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} /*"~",94*/
}; 

//取模方式：
//字体:Default
//逐行式，逆向（低位在前） 
//常用ASCII表
//偏移量32
//ASCII字符集
//偏移量32
//大小:16*8
code unsigned char asc2_1608[95][16]={
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/
{0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x18,0x18,0x00,0x00},/*"!",1*/
{0x00,0x48,0x6C,0x24,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*""",2*/
{0x00,0x00,0x00,0x24,0x24,0x24,0x7F,0x12,0x12,0x12,0x7F,0x12,0x12,0x12,0x00,0x00},/*"#",3*/
{0x00,0x00,0x08,0x1C,0x2A,0x2A,0x0A,0x0C,0x18,0x28,0x28,0x2A,0x2A,0x1C,0x08,0x08},/*"$",4*/
{0x00,0x00,0x00,0x22,0x25,0x15,0x15,0x15,0x2A,0x58,0x54,0x54,0x54,0x22,0x00,0x00},/*"%",5*/
{0x00,0x00,0x00,0x0C,0x12,0x12,0x12,0x0A,0x76,0x25,0x29,0x11,0x91,0x6E,0x00,0x00},/*"&",6*/
{0x00,0x06,0x06,0x04,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",7*/
{0x00,0x40,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x20,0x40,0x00},/*"(",8*/
{0x00,0x02,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04,0x02,0x00},/*")",9*/
{0x00,0x00,0x00,0x00,0x08,0x08,0x6B,0x1C,0x1C,0x6B,0x08,0x08,0x00,0x00,0x00,0x00},/*"*",10*/
{0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x7F,0x08,0x08,0x08,0x08,0x00,0x00,0x00},/*"+",11*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x04,0x03},/*",",12*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"-",13*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x00,0x00},/*".",14*/
{0x00,0x00,0x80,0x40,0x40,0x20,0x20,0x10,0x10,0x08,0x08,0x04,0x04,0x02,0x02,0x00},/*"/",15*/
{0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00},/*"0",16*/
{0x00,0x00,0x00,0x08,0x0E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"1",17*/
{0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x20,0x20,0x10,0x08,0x04,0x42,0x7E,0x00,0x00},/*"2",18*/
{0x00,0x00,0x00,0x3C,0x42,0x42,0x20,0x18,0x20,0x40,0x40,0x42,0x22,0x1C,0x00,0x00},/*"3",19*/
{0x00,0x00,0x00,0x20,0x30,0x28,0x24,0x24,0x22,0x22,0x7E,0x20,0x20,0x78,0x00,0x00},/*"4",20*/
{0x00,0x00,0x00,0x7E,0x02,0x02,0x02,0x1A,0x26,0x40,0x40,0x42,0x22,0x1C,0x00,0x00},/*"5",21*/
{0x00,0x00,0x00,0x38,0x24,0x02,0x02,0x1A,0x26,0x42,0x42,0x42,0x24,0x18,0x00,0x00},/*"6",22*/
{0x00,0x00,0x00,0x7E,0x22,0x22,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00},/*"7",23*/	 
{0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00},/*"8",24*/
{0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x64,0x58,0x40,0x40,0x24,0x1C,0x00,0x00},/*"9",25*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00},/*":",26*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x04},/*";",27*/
{0x00,0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x20,0x40,0x00,0x00},/*"<",28*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00},/*"=",29*/
{0x00,0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x02,0x00,0x00},/*">",30*/
{0x00,0x00,0x00,0x3C,0x42,0x42,0x46,0x40,0x20,0x10,0x10,0x00,0x18,0x18,0x00,0x00},/*"?",31*/
{0x00,0x00,0x00,0x1C,0x22,0x5A,0x55,0x55,0x55,0x55,0x2D,0x42,0x22,0x1C,0x00,0x00},/*"@",32*/
{0x00,0x00,0x00,0x08,0x08,0x18,0x14,0x14,0x24,0x3C,0x22,0x42,0x42,0xE7,0x00,0x00},/*"A",33*/
{0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x1E,0x22,0x42,0x42,0x42,0x22,0x1F,0x00,0x00},/*"B",34*/
{0x00,0x00,0x00,0x7C,0x42,0x42,0x01,0x01,0x01,0x01,0x01,0x42,0x22,0x1C,0x00,0x00},/*"C",35*/
{0x00,0x00,0x00,0x1F,0x22,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1F,0x00,0x00},/*"D",36*/
{0x00,0x00,0x00,0x3F,0x42,0x12,0x12,0x1E,0x12,0x12,0x02,0x42,0x42,0x3F,0x00,0x00},/*"E",37*/
{0x00,0x00,0x00,0x3F,0x42,0x12,0x12,0x1E,0x12,0x12,0x02,0x02,0x02,0x07,0x00,0x00},/*"F",38*/
{0x00,0x00,0x00,0x3C,0x22,0x22,0x01,0x01,0x01,0x71,0x21,0x22,0x22,0x1C,0x00,0x00},/*"G",39*/
{0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x42,0xE7,0x00,0x00},/*"H",40*/
{0x00,0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"I",41*/
{0x00,0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x11,0x0F},/*"J",42*/
{0x00,0x00,0x00,0x77,0x22,0x12,0x0A,0x0E,0x0A,0x12,0x12,0x22,0x22,0x77,0x00,0x00},/*"K",43*/
{0x00,0x00,0x00,0x07,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x42,0x7F,0x00,0x00},/*"L",44*/
{0x00,0x00,0x00,0x77,0x36,0x36,0x36,0x36,0x2A,0x2A,0x2A,0x2A,0x2A,0x6B,0x00,0x00},/*"M",45*/
{0x00,0x00,0x00,0xE3,0x46,0x46,0x4A,0x4A,0x52,0x52,0x52,0x62,0x62,0x47,0x00,0x00},/*"N",46*/
{0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x1C,0x00,0x00},/*"O",47*/
{0x00,0x00,0x00,0x3F,0x42,0x42,0x42,0x42,0x3E,0x02,0x02,0x02,0x02,0x07,0x00,0x00},/*"P",48*/
{0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x4D,0x53,0x32,0x1C,0x60,0x00},/*"Q",49*/
{0x00,0x00,0x00,0x3F,0x42,0x42,0x42,0x3E,0x12,0x12,0x22,0x22,0x42,0xC7,0x00,0x00},/*"R",50*/
{0x00,0x00,0x00,0x7C,0x42,0x42,0x02,0x04,0x18,0x20,0x40,0x42,0x42,0x3E,0x00,0x00},/*"S",51*/
{0x00,0x00,0x00,0x7F,0x49,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x1C,0x00,0x00},/*"T",52*/
{0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00},/*"U",53*/
{0x00,0x00,0x00,0xE7,0x42,0x42,0x22,0x24,0x24,0x14,0x14,0x18,0x08,0x08,0x00,0x00},/*"V",54*/
{0x00,0x00,0x00,0x6B,0x49,0x49,0x49,0x49,0x55,0x55,0x36,0x22,0x22,0x22,0x00,0x00},/*"W",55*/
{0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x18,0x18,0x18,0x24,0x24,0x42,0xE7,0x00,0x00},/*"X",56*/
{0x00,0x00,0x00,0x77,0x22,0x22,0x14,0x14,0x08,0x08,0x08,0x08,0x08,0x1C,0x00,0x00},/*"Y",57*/
{0x00,0x00,0x00,0x7E,0x21,0x20,0x10,0x10,0x08,0x04,0x04,0x42,0x42,0x3F,0x00,0x00},/*"Z",58*/
{0x00,0x78,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x78,0x00},/*"[",59*/
{0x00,0x00,0x02,0x02,0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x20,0x20,0x20,0x40,0x40},/*"\",60*/
{0x00,0x1E,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1E,0x00},/*"]",61*/
{0x00,0x38,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"^",62*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},/*"_",63*/
{0x00,0x06,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"`",64*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x78,0x44,0x42,0x42,0xFC,0x00,0x00},/*"a",65*/
{0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x1A,0x26,0x42,0x42,0x42,0x26,0x1A,0x00,0x00},/*"b",66*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x02,0x02,0x02,0x44,0x38,0x00,0x00},/*"c",67*/
{0x00,0x00,0x00,0x60,0x40,0x40,0x40,0x78,0x44,0x42,0x42,0x42,0x64,0xD8,0x00,0x00},/*"d",68*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x7E,0x02,0x02,0x42,0x3C,0x00,0x00},/*"e",69*/
{0x00,0x00,0x00,0xF0,0x88,0x08,0x08,0x7E,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"f",70*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x22,0x22,0x1C,0x02,0x3C,0x42,0x42,0x3C},/*"g",71*/
{0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x3A,0x46,0x42,0x42,0x42,0x42,0xE7,0x00,0x00},/*"h",72*/
{0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x0E,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"i",73*/
{0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x38,0x20,0x20,0x20,0x20,0x20,0x20,0x22,0x1E},/*"j",74*/
{0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x72,0x12,0x0A,0x16,0x12,0x22,0x77,0x00,0x00},/*"k",75*/
{0x00,0x00,0x00,0x0E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"l",76*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x92,0x92,0x92,0x92,0x92,0xB7,0x00,0x00},/*"m",77*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3B,0x46,0x42,0x42,0x42,0x42,0xE7,0x00,0x00},/*"n",78*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00},/*"o",79*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1B,0x26,0x42,0x42,0x42,0x22,0x1E,0x02,0x07},/*"p",80*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x44,0x42,0x42,0x42,0x44,0x78,0x40,0xE0},/*"q",81*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x4C,0x04,0x04,0x04,0x04,0x1F,0x00,0x00},/*"r",82*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x42,0x02,0x3C,0x40,0x42,0x3E,0x00,0x00},/*"s",83*/
{0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x3E,0x08,0x08,0x08,0x08,0x08,0x30,0x00,0x00},/*"t",84*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x63,0x42,0x42,0x42,0x42,0x62,0xDC,0x00,0x00},/*"u",85*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x14,0x08,0x08,0x00,0x00},/*"v",86*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEB,0x49,0x49,0x55,0x55,0x22,0x22,0x00,0x00},/*"w",87*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x76,0x24,0x18,0x18,0x18,0x24,0x6E,0x00,0x00},/*"x",88*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x14,0x18,0x08,0x08,0x07},/*"y",89*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x22,0x10,0x08,0x08,0x44,0x7E,0x00,0x00},/*"z",90*/
{0x00,0xC0,0x20,0x20,0x20,0x20,0x20,0x10,0x20,0x20,0x20,0x20,0x20,0x20,0xC0,0x00},/*"{",91*/
{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},/*"|",92*/
{0x00,0x06,0x08,0x08,0x08,0x08,0x08,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x06,0x00},/*"}",93*/
{0x0C,0x32,0xC2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"~",94*/
};

//宋体，逐行式，顺向（高位在前）
//大小:16x16 
typedef struct 
{
       unsigned char Index[2];	
       char Msk[32];
}typFNT_GB16; 
//纯色填充测试矩形画圆图片显示菜单全动电子技术有限公司欢迎您综合测试程序版权所有
code typFNT_GB16 tfont16[]=
{
"深",0x00,0x00,0x27,0xFC,0x14,0x04,0x14,0xA4,0x81,0x10,0x42,0x08,0x40,0x40,0x10,0x40,
0x17,0xFC,0x20,0x40,0xE0,0xE0,0x21,0x50,0x22,0x48,0x2C,0x46,0x20,0x40,0x00,0x40,/*0*/
"圳",0x11,0x04,0x11,0x24,0x11,0x24,0x11,0x24,0x11,0x24,0xFD,0x24,0x11,0x24,0x11,0x24,
0x11,0x24,0x11,0x24,0x11,0x24,0x1D,0x24,0xE1,0x24,0x42,0x24,0x02,0x04,0x04,0x04,/*1*/
"市",0x02,0x00,0x01,0x00,0x00,0x00,0x7F,0xFC,0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,
0x21,0x08,0x21,0x08,0x21,0x08,0x21,0x08,0x21,0x28,0x21,0x10,0x01,0x00,0x01,0x00,/*2*/
"全",0x00,0x00,0x00,0x00,0x01,0x80,0x02,0x40,0x04,0x30,0x18,0x08,0x60,0x06,0x1F,0xF9,
0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,0x01,0x00,0x7F,0xFE,/*0*/
"动",0x00,0x00,0x00,0x00,0x00,0x20,0x3E,0x20,0x00,0x7C,0x00,0x22,0x00,0x22,0x7F,0x22,
0x10,0x22,0x10,0x22,0x12,0x22,0x12,0x22,0x22,0x42,0x23,0x42,0x3D,0x82,0x00,0x9C,/*1*/
"电",0x00,0x00,0x01,0x00,0x01,0x00,0x1F,0xF0,0x61,0x0C,0x41,0x04,0x41,0x04,0x7F,0xFC,
0x41,0x04,0x41,0x04,0x41,0x04,0x7F,0xFC,0x01,0x00,0x01,0x02,0x01,0x02,0x01,0xFC,/*2*/
"子",0x00,0x00,0x00,0x00,0x3F,0xF8,0x00,0x10,0x00,0x60,0x00,0x80,0x01,0x00,0x00,0x80,
0x7F,0xFE,0x00,0x40,0x00,0x40,0x00,0x20,0x00,0x20,0x00,0x20,0x18,0x40,0x07,0x80,/*3*/
"技",0x00,0x00,0x00,0x00,0x10,0x40,0x13,0xFE,0x10,0x40,0x7C,0x40,0x10,0x40,0x13,0xFC,
0x11,0x04,0x19,0x08,0x30,0x88,0x50,0x50,0x10,0x60,0x10,0xD0,0x13,0x08,0x7C,0x06,/*0*/
"术",0x00,0x00,0x01,0x00,0x01,0x30,0x01,0x08,0x01,0x00,0x7F,0xFE,0x01,0x80,0x03,0x40,
0x05,0x40,0x05,0x20,0x09,0x10,0x11,0x08,0x21,0x04,0x41,0x02,0x01,0x00,0x01,0x00,/*1*/
"有",0x00,0x00,0x01,0x00,0x02,0x00,0x7F,0xFE,0x04,0x00,0x08,0x00,0x1F,0xFC,0x70,0x04,
0x90,0x04,0x1F,0xFC,0x10,0x04,0x10,0x04,0x1F,0xFC,0x10,0x04,0x10,0x04,0x10,0x3C,/*2*/
"限",0x00,0x00,0x00,0x00,0x7B,0xFC,0x4A,0x04,0x4A,0x04,0x4B,0xFC,0x52,0x04,0x4A,0x04,
0x4B,0xFC,0x4A,0x40,0x4A,0x44,0x7A,0x28,0x42,0x30,0x42,0x10,0x42,0x08,0x43,0xC6,/*3*/
"公",0x00,0x00,0x00,0x00,0x04,0x40,0x04,0x20,0x08,0x10,0x10,0x10,0x10,0x08,0x21,0x04,
0x42,0x02,0x02,0x20,0x04,0x10,0x08,0x10,0x08,0x08,0x10,0x08,0x1F,0xFC,0x00,0x04,/*4*/
"司",0x00,0x00,0x00,0x00,0x3F,0xFC,0x00,0x04,0x00,0x04,0x3F,0xF4,0x00,0x04,0x3F,0xE4,
0x20,0x24,0x20,0x24,0x20,0x24,0x20,0x24,0x20,0x24,0x1F,0xC4,0x00,0x04,0x00,0x7C,/*5*/
"欢",0x00,0x00,0x00,0x00,0x00,0x80,0x7E,0xFC,0x02,0xA2,0x02,0xA2,0x22,0xA4,0x15,0x24,
0x14,0x24,0x0C,0x30,0x0C,0x30,0x0C,0x48,0x12,0x48,0x22,0x84,0x42,0x84,0x01,0x02,/*6*/
"迎",0x00,0x00,0x00,0x00,0x23,0x98,0x24,0x64,0x14,0x44,0x04,0x44,0x64,0x44,0x14,0x44,
0x14,0x44,0x14,0x44,0x14,0x44,0x15,0xC4,0x12,0x5C,0x10,0x40,0x28,0x40,0x47,0xFE,/*7*/
"您",0x00,0x00,0x00,0x00,0x12,0x00,0x13,0xFE,0x24,0x22,0x25,0x22,0x65,0x28,0x62,0x24,
0x22,0x24,0x24,0x20,0x20,0xE0,0x05,0x08,0x14,0x84,0x24,0x44,0x24,0x1A,0x47,0xF2,/*8*/
"纯",0x00,0x00,0x00,0x20,0x10,0x20,0x13,0xFE,0x20,0x20,0x26,0x24,0x4A,0x24,0x7A,0x24,
0x12,0x24,0x22,0x24,0x23,0xFC,0x7C,0x20,0x00,0x22,0x04,0x22,0x78,0x22,0x00,0x3C,/*0*/
"色",0x00,0x00,0x00,0x00,0x04,0x00,0x0F,0xF0,0x10,0x20,0x20,0x20,0x7F,0xFC,0x20,0x84,
0x20,0x84,0x20,0x84,0x20,0x84,0x3F,0xF8,0x20,0x00,0x20,0x02,0x20,0x02,0x1F,0xFE,/*1*/
"填",0x00,0x00,0x00,0x00,0x20,0x40,0x23,0xFE,0x20,0x40,0x79,0xFC,0x22,0x04,0x23,0xFC,
0x22,0x04,0x23,0xFC,0x22,0x04,0x23,0xFC,0x3A,0x04,0x65,0xFA,0x01,0x98,0x02,0x04,/*2*/
"充",0x00,0x00,0x01,0x00,0x01,0x00,0x7F,0xFE,0x02,0x20,0x04,0x10,0x04,0x08,0x08,0x04,
0x3F,0xFC,0x04,0x42,0x04,0x40,0x04,0x40,0x04,0x42,0x08,0x42,0x10,0x42,0x60,0x7E,/*3*/
"矩",0x00,0x00,0x00,0x00,0x20,0x7E,0x3E,0x80,0x48,0x80,0x48,0x80,0x48,0xFE,0x48,0x82,
0x7F,0x82,0x08,0x82,0x0C,0x82,0x14,0xFA,0x12,0x84,0x22,0x80,0x21,0x80,0x40,0xFE,/*6*/
"形",0x00,0x00,0x00,0x00,0x7F,0x84,0x22,0x08,0x22,0x30,0x22,0xC0,0x22,0x02,0x22,0x04,
0x7F,0xC8,0x22,0x30,0x22,0xC2,0x22,0x02,0x22,0x04,0x22,0x08,0x22,0x30,0x40,0x40,/*7*/
"画",0x00,0x00,0x00,0x00,0x7F,0xFE,0x00,0x00,0x0F,0xF0,0x11,0x10,0x11,0x10,0x11,0x10,
0x51,0x12,0x5F,0xF2,0x51,0x12,0x51,0x12,0x51,0x12,0x4F,0xF2,0x40,0x02,0x7F,0xFC,/*8*/
"圆",0x00,0x00,0x00,0x00,0x7F,0xFE,0x47,0xE2,0x48,0x12,0x48,0x12,0x47,0xE2,0x4F,0xF2,
0x50,0x12,0x50,0x12,0x51,0x12,0x51,0x12,0x42,0x92,0x44,0x72,0x58,0x0A,0x3F,0xFC,/*9*/
"三",0x00,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xF8,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00,/*13*/
"角",0x08,0x00,0x08,0x00,0x1F,0xE0,0x20,0x20,0x40,0x40,0xBF,0xF8,0x21,0x08,0x21,0x08,
0x3F,0xF8,0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,0x41,0x08,0x41,0x28,0x80,0x10,/*14*/
"图",0x00,0x00,0x00,0x00,0x3F,0xFE,0x44,0x02,0x47,0xF2,0x4C,0x22,0x53,0x62,0x40,0x82,
0x43,0x62,0x5E,0x1A,0x41,0x82,0x40,0x62,0x43,0x02,0x40,0xC2,0x40,0x22,0x3F,0xFC,/*0*/
"片",0x00,0x00,0x00,0x40,0x20,0x40,0x20,0x40,0x20,0x40,0x3F,0xFE,0x20,0x00,0x20,0x00,
0x20,0x00,0x3F,0xE0,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x40,0x10,0x40,0x10,/*1*/
"显",0x00,0x00,0x00,0x00,0x3F,0xFC,0x20,0x04,0x20,0x04,0x3F,0xFC,0x20,0x04,0x20,0x04,
0x1F,0xF8,0x24,0x44,0x14,0x48,0x14,0x48,0x14,0x48,0x0C,0x50,0x04,0x40,0x7F,0xFE,/*2*/
"示",0x00,0x00,0x00,0x00,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFE,0x00,0x80,
0x08,0x90,0x08,0x88,0x10,0x88,0x10,0x84,0x20,0x84,0x20,0x82,0x40,0x82,0x07,0x80,/*3*/
"菜",0x00,0x00,0x00,0x20,0x08,0x20,0x7F,0xFE,0x00,0x20,0x00,0x78,0x3F,0x88,0x11,0x08,
0x08,0x90,0x09,0x20,0x7F,0xFE,0x01,0x80,0x03,0x40,0x0D,0x30,0x31,0x0C,0x40,0x02,/*4*/
"单",0x00,0x00,0x00,0x10,0x08,0x10,0x04,0x20,0x3F,0xF8,0x21,0x04,0x21,0x04,0x3F,0xFC,
0x21,0x04,0x21,0x04,0x3F,0xF8,0x01,0x00,0x7F,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,/*5*/
"中",0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xFC,0x21,0x04,0x21,0x04,0x21,0x04,
0x21,0x04,0x21,0x04,0x21,0x04,0x3F,0xFC,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,/*0*/
"英",0x00,0x00,0x00,0x00,0x08,0x20,0x7F,0xFE,0x08,0x20,0x09,0x20,0x01,0x00,0x3F,0xF8,
0x21,0x08,0x21,0x08,0x21,0x08,0x1F,0xF4,0x01,0x40,0x02,0x20,0x0C,0x10,0x70,0x0E,/*1*/
"文",0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x80,0x3F,0x7C,0x08,0x10,0x08,0x10,0x04,0x10,
0x04,0x20,0x02,0x20,0x02,0x40,0x01,0x80,0x01,0x80,0x02,0x60,0x1C,0x18,0xE0,0x06,/*2*/
"综",0x00,0x00,0x00,0x00,0x10,0x20,0x11,0xFE,0x22,0x02,0x22,0x02,0x49,0xFC,0x58,0x00,
0x30,0x00,0x13,0xFE,0x25,0x28,0x79,0x24,0x01,0x24,0x0D,0x24,0x72,0x22,0x02,0xA2,/*4*/
"合",0x00,0x00,0x00,0x00,0x01,0x80,0x02,0x40,0x04,0x30,0x18,0x08,0x60,0x06,0x1F,0xF8,
0x00,0x00,0x1F,0xF8,0x20,0x04,0x20,0x04,0x20,0x04,0x20,0x04,0x20,0x04,0x1F,0xF8,/*5*/
"亮",0x00,0x00,0x01,0x00,0x01,0x00,0x7F,0xFE,0x00,0x00,0x3F,0xF8,0x20,0x08,0x3F,0xF8,
0x3F,0xF8,0x40,0x06,0x47,0xC2,0x48,0x24,0x08,0x20,0x08,0x22,0x10,0x22,0x60,0x3E,/*0*/
"度",0x00,0x00,0x00,0x00,0x00,0x80,0x3F,0xFE,0x44,0x10,0x5F,0xFC,0x44,0x10,0x44,0x10,
0x43,0xF0,0x40,0x00,0x5F,0xF8,0x44,0x08,0x42,0x30,0x41,0xC0,0x43,0x60,0xBC,0x1E,/*1*/
"测",0x00,0x00,0x00,0x00,0x67,0xC2,0x14,0x52,0x05,0x52,0x05,0x52,0xC5,0x52,0x25,0x52,
0x05,0x52,0x05,0x52,0x15,0x52,0x17,0x52,0x22,0x82,0x22,0x42,0x44,0x42,0x48,0x3E,/*2*/
"试",0x00,0x00,0x00,0x00,0x20,0x14,0x10,0x14,0x17,0xFE,0x00,0x12,0x00,0x10,0x60,0x10,
0x13,0xF0,0x10,0x90,0x10,0x90,0x10,0x90,0x14,0x92,0x14,0xEA,0x1F,0x0A,0x00,0x06,/*3*/
"程",0x00,0x00,0x00,0x00,0x19,0xFE,0x72,0x02,0x12,0x02,0x12,0x02,0x7D,0xFC,0x18,0x00,
0x1B,0xFE,0x34,0x20,0x50,0x20,0x53,0xFE,0x10,0x20,0x10,0x20,0x10,0x20,0x13,0xFE,/*8*/
"序",0x00,0x00,0x00,0x00,0x00,0x80,0x3F,0xFE,0x40,0x00,0x47,0xFC,0x42,0x08,0x41,0x30,
0x40,0xC0,0x5F,0xFE,0x40,0x42,0x40,0x42,0x40,0x44,0x40,0x48,0x40,0x40,0x44,0x40,/*9*/
"调",0x00,0x00,0x00,0x00,0x23,0xFE,0x12,0x22,0x02,0xFA,0x02,0x22,0xE2,0x22,0x12,0xFE,
0x12,0x72,0x12,0x8A,0x12,0x8A,0x12,0x8A,0x16,0xBA,0x1A,0x42,0x12,0x02,0x04,0x0E,/*0*/
"光",0x00,0x00,0x01,0x00,0x01,0x04,0x11,0x08,0x09,0x08,0x09,0x10,0x09,0x20,0x7F,0xFE,
0x04,0x40,0x04,0x40,0x04,0x40,0x04,0x40,0x08,0x42,0x08,0x42,0x10,0x42,0x60,0x7C,/*1*/
"版",0x00,0x00,0x00,0x00,0x48,0xFE,0x49,0x00,0x49,0x00,0x49,0x00,0x7E,0xFE,0x41,0x82,
0x41,0x44,0x79,0x44,0x45,0x28,0x45,0x28,0x45,0x10,0x45,0x28,0x46,0x44,0x03,0x82,/*10*/
"权",0x00,0x00,0x10,0x00,0x10,0x00,0x13,0xFC,0x7D,0x04,0x11,0x04,0x19,0x04,0x18,0x84,
0x34,0x88,0x50,0x48,0x50,0x50,0x10,0x20,0x10,0x50,0x10,0x88,0x13,0x04,0x14,0x02,/*11*/
"所",0x00,0x00,0x00,0x00,0x3F,0x7C,0x20,0x40,0x20,0x40,0x3E,0x40,0x22,0x7E,0x22,0x44,
0x22,0x44,0x22,0x44,0x3E,0x84,0x20,0x84,0x20,0x84,0x40,0x84,0x41,0x04,0x42,0x04,/*12*/
"屏",0x00,0x00,0x3F,0xF8,0x20,0x08,0x20,0x08,0x3F,0xF8,0x24,0x10,0x22,0x20,0x2F,0xF8,
0x22,0x20,0x22,0x20,0x3F,0xFC,0x22,0x20,0x42,0x20,0x44,0x20,0x84,0x20,0x08,0x20,/*"?",0*/
"幕",0x04,0x40,0x7F,0xFC,0x04,0x40,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0x1F,0xF0,
0x04,0x00,0xFF,0xFE,0x11,0x10,0x3F,0xF8,0xD1,0x16,0x11,0x50,0x11,0x20,0x01,0x00,/*"?",1*/
"旋",0x20,0x80,0x10,0x80,0x10,0xFE,0x01,0x00,0xFE,0x00,0x21,0xFC,0x20,0x24,0x3C,0x24,
0x24,0xA0,0x24,0xA0,0x24,0xBC,0x24,0xA0,0x24,0xA0,0x45,0x60,0x55,0x3E,0x8A,0x00,/*"?",2*/
"转",0x20,0x20,0x20,0x20,0x20,0x20,0xFD,0xFC,0x40,0x20,0x50,0x40,0x93,0xFE,0xFC,0x40,
0x10,0x80,0x11,0xFC,0x1C,0x04,0xF0,0x88,0x50,0x50,0x10,0x20,0x10,0x10,0x10,0x10,/*"?",3*/
"开",0x00,0x00,0x7F,0xFC,0x08,0x20,0x08,0x20,0x08,0x20,0x08,0x20,0x08,0x20,0xFF,0xFE,
0x08,0x20,0x08,0x20,0x08,0x20,0x08,0x20,0x10,0x20,0x10,0x20,0x20,0x20,0x40,0x20,/*"?",0*/
"源",0x00,0x00,0x27,0xFE,0x14,0x20,0x14,0x40,0x85,0xFC,0x45,0x04,0x45,0xFC,0x15,0x04,
0x15,0xFC,0x25,0x24,0xE4,0x20,0x24,0xA8,0x29,0x24,0x2A,0x22,0x30,0xA0,0x00,0x40,/*"?",1*/
"液",0x00,0x80,0x20,0x40,0x17,0xFE,0x11,0x20,0x81,0x20,0x42,0x3C,0x42,0x44,0x16,0x64,
0x12,0x94,0x23,0x48,0xE2,0x48,0x22,0x30,0x22,0x20,0x22,0x50,0x22,0x88,0x03,0x06,/*"?",2*/
"晶",0x0F,0xE0,0x08,0x20,0x08,0x20,0x0F,0xE0,0x08,0x20,0x08,0x20,0x0F,0xE0,0x00,0x00,
0x7E,0xFC,0x42,0x84,0x42,0x84,0x7E,0xFC,0x42,0x84,0x42,0x84,0x7E,0xFC,0x42,0x84,/*"?",3*/
"网",0x00,0x00,0x7F,0xFC,0x40,0x04,0x40,0x04,0x42,0x14,0x52,0x94,0x4A,0x54,0x44,0x24,
0x44,0x24,0x4A,0x54,0x4A,0x54,0x52,0x94,0x61,0x04,0x40,0x04,0x40,0x14,0x40,0x08,/*"?",4*/
"站",0x10,0x20,0x08,0x20,0x08,0x20,0x7E,0x20,0x00,0x3E,0x04,0x20,0x44,0x20,0x44,0x20,
0x25,0xFC,0x29,0x04,0x29,0x04,0x0F,0x04,0xF1,0x04,0x41,0x04,0x01,0xFC,0x01,0x04,/*"?",5*/
"按",0x10,0x40,0x10,0x20,0x10,0x20,0x13,0xFE,0xFA,0x02,0x14,0x44,0x10,0x40,0x1B,0xFE,
0x30,0x88,0xD0,0x88,0x11,0x08,0x10,0xD0,0x10,0x20,0x10,0x50,0x50,0x88,0x23,0x04,/*"?",6*/
"键",0x20,0x10,0x20,0x10,0x3B,0x7C,0x21,0x14,0x41,0xFE,0x7A,0x14,0xA2,0x7C,0x27,0x10,
0xF9,0x7C,0x25,0x10,0x25,0xFE,0x22,0x10,0x2A,0x10,0x35,0x00,0x28,0xFE,0x00,0x00,/*"?",0*/
"校",0x10,0x40,0x10,0x20,0x10,0x20,0x11,0xFE,0xFC,0x00,0x10,0x88,0x31,0x04,0x3A,0x02,
0x54,0x88,0x50,0x88,0x90,0x50,0x10,0x50,0x10,0x20,0x10,0x50,0x10,0x88,0x13,0x06,/*"?",7*/
"准",0x01,0x40,0x41,0x20,0x21,0x20,0x23,0xFE,0x02,0x20,0x16,0x20,0x1B,0xFC,0x12,0x20,
0x22,0x20,0x23,0xFC,0xE2,0x20,0x22,0x20,0x22,0x20,0x23,0xFE,0x22,0x00,0x02,0x00,/*"?",8*/
"触",0x20,0x20,0x20,0x20,0x78,0x20,0x49,0xFC,0x91,0x24,0x7D,0x24,0x55,0x24,0x55,0x24,
0x7D,0xFC,0x55,0x24,0x54,0x20,0x7C,0x28,0x54,0x24,0x57,0xFE,0x45,0x02,0x8C,0x00,/*"?",9*/
"摸",0x11,0x10,0x11,0x10,0x17,0xFC,0x11,0x10,0xFC,0x00,0x13,0xF8,0x12,0x08,0x17,0xF8,
0x1A,0x08,0x33,0xF8,0xD0,0x40,0x17,0xFC,0x10,0xA0,0x11,0x10,0x52,0x08,0x24,0x06,/*"?",10*/
"读",0x00,0x20,0x20,0x20,0x11,0xFC,0x10,0x20,0x00,0x20,0x03,0xFE,0xF0,0x02,0x10,0x94,
0x10,0x50,0x11,0x10,0x10,0x90,0x13,0xFE,0x14,0x28,0x18,0x44,0x10,0x82,0x03,0x02,/*"?",0*/
"和",0x04,0x00,0x0E,0x00,0x78,0x00,0x08,0x7C,0x08,0x44,0xFF,0x44,0x08,0x44,0x18,0x44,
0x1C,0x44,0x2A,0x44,0x2A,0x44,0x48,0x44,0x88,0x7C,0x08,0x44,0x08,0x00,0x08,0x00,/*"?",0*/
"颜",0x10,0x00,0x08,0xFE,0x7F,0x10,0x22,0x20,0x14,0x7C,0x7F,0x44,0x44,0x54,0x48,0x54,
0x52,0x54,0x44,0x54,0x48,0x54,0x51,0x54,0x42,0x28,0x44,0x24,0x88,0x42,0x30,0x82,/*"?",0*/
"值",0x08,0x40,0x08,0x40,0x0F,0xFC,0x10,0x40,0x10,0x40,0x33,0xF8,0x32,0x08,0x53,0xF8,
0x92,0x08,0x13,0xF8,0x12,0x08,0x13,0xF8,0x12,0x08,0x12,0x08,0x1F,0xFE,0x10,0x00,/*"?",0*/
};

//宋体，逐行式，顺向（高位在前）
//大小:24x24 
typedef struct 
{
       unsigned char Index[2];	
       char Msk[72];
}typFNT_GB24; 
code typFNT_GB24 tfont24[]=
{
"深",0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x08,0x00,0x08,0x0C,0x7F,0xFC,0x04,
0x40,0x10,0x01,0xC8,0xA0,0x02,0x18,0x60,0x42,0x30,0x18,0x32,0x23,0x18,0x12,0xC3,
0x00,0x14,0x03,0x00,0x04,0x03,0x0C,0x04,0x7F,0xF0,0x08,0x0F,0x80,0x08,0x0B,0x40,
0x78,0x13,0x60,0x18,0x33,0x20,0x18,0x63,0x18,0x18,0x83,0x1C,0x19,0x03,0x08,0x18,
0x03,0x00,0x00,0x03,0x00,0x00,0x00,0x00,/*0*/
"圳",0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x10,0x0C,0x04,0x18,0x0C,0x04,0x10,0x8C,0x04,
0x10,0x8C,0x04,0x10,0x8C,0x04,0x10,0x8C,0x04,0xD0,0x8C,0x3F,0x10,0x8C,0x04,0x10,
0x8C,0x04,0x10,0x8C,0x04,0x10,0x8C,0x04,0x10,0x8C,0x04,0x10,0x8C,0x04,0x10,0x8C,
0x05,0xF0,0x8C,0x0E,0x20,0x8C,0x78,0x20,0x8C,0x20,0x40,0x8C,0x00,0x80,0x8C,0x01,
0x00,0x0C,0x02,0x00,0x0C,0x00,0x00,0x00,/*1*/
"市",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x18,0x00,0x00,0x18,0x08,0x00,
0x00,0x1C,0x1F,0xFF,0xE0,0x00,0x18,0x00,0x00,0x18,0x20,0x07,0xFF,0xF0,0x04,0x18,
0x20,0x04,0x18,0x20,0x04,0x18,0x20,0x04,0x18,0x20,0x04,0x18,0x20,0x04,0x18,0x20,
0x04,0x18,0x20,0x04,0x18,0x20,0x04,0x18,0x20,0x04,0x18,0xE0,0x04,0x18,0x40,0x00,
0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,/*2*/
"中",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,
0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x3F,0xFF,0xFE,0x30,0x18,0x06,0x30,0x18,
0x06,0x30,0x18,0x06,0x30,0x18,0x06,0x30,0x18,0x06,0x3F,0xFF,0xFE,0x30,0x18,0x06,
0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*0*/
"文",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x1C,0x00,0x00,
0x06,0x00,0xFF,0xFF,0xFF,0x06,0x00,0x30,0x06,0x00,0x30,0x03,0x00,0x60,0x03,0x00,
0x60,0x01,0x80,0xC0,0x00,0xC1,0x80,0x00,0xE3,0x00,0x00,0x36,0x00,0x00,0x1C,0x00,
0x00,0x77,0x00,0x03,0xC1,0xE0,0x1E,0x00,0x3C,0x60,0x00,0x07,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*1*/
"测",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x03,0x21,
0xFF,0x33,0x39,0x83,0x33,0x11,0x83,0x33,0x01,0x9B,0x33,0xC1,0x9B,0x33,0x71,0x9B,
0x33,0x19,0x9B,0x33,0x01,0x9B,0x33,0x01,0x9B,0x33,0x11,0x9B,0x33,0x19,0xB3,0x33,
0x30,0x30,0x33,0x30,0x6C,0x03,0x30,0xC6,0x03,0x63,0x83,0x03,0x2E,0x01,0xBE,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*2*/
"试",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0xD8,0x30,
0x00,0xCE,0x18,0x00,0xC2,0x1C,0x00,0xC0,0x01,0xFF,0xFF,0x00,0x00,0xC0,0xF8,0x00,
0xC0,0x18,0x00,0xC0,0x19,0xFF,0xC0,0x18,0x18,0x40,0x18,0x18,0x60,0x19,0x18,0x60,
0x1B,0x18,0x61,0x1E,0x18,0x31,0x1C,0x1F,0xB1,0x39,0xF0,0x19,0x10,0x00,0x0F,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*3*/
};  

//宋体，逐行式，顺向（高位在前）
//大小:32x32 
typedef struct 
{
       unsigned char Index[2];	
       char Msk[128];
}typFNT_GB32; 
code typFNT_GB32 tfont32[]=
{
"字",0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0xC0,0x00,
0x00,0x01,0xC0,0xC0,0x00,0x01,0x07,0xC0,0x00,0x01,0xFF,0x00,0x02,0x1F,0xFE,0x00,
0x07,0xF0,0x1C,0x00,0x07,0xC0,0x70,0x00,0x0F,0x00,0xE0,0x00,0x0E,0x03,0xF0,0x00,
0x1C,0x0F,0xF0,0x00,0x3C,0x0F,0x70,0x00,0x3C,0x00,0xE0,0x00,0x18,0x00,0xC0,0x00,
0x00,0x00,0xC0,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x20,0x00,
0x00,0x00,0x37,0x00,0x00,0x01,0xFF,0x00,0x00,0x7F,0xF8,0x00,0x07,0xF8,0x30,0x00,
0x1F,0x80,0x30,0x00,0x00,0x80,0x30,0x00,0x00,0xC0,0x30,0x00,0x00,0x60,0x60,0x00,
0x00,0x18,0xE0,0x00,0x00,0x0F,0xC0,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,/*0*/
"体",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0xE0,
0x00,0x20,0x01,0xB8,0x00,0x70,0x3F,0xF8,0x00,0x61,0xFF,0xC0,0x00,0xC3,0x03,0x00,
0x01,0xC6,0x06,0x00,0x03,0x8C,0x06,0x00,0x03,0x08,0x0C,0x00,0x06,0x08,0x0C,0x00,
0x0E,0x18,0x18,0x3F,0x1E,0x10,0x1B,0xF3,0x1F,0x90,0x3F,0x07,0x00,0x80,0x3C,0x1C,
0x01,0x90,0x70,0x7C,0x01,0x90,0x60,0xFE,0x01,0xA0,0xC3,0xF8,0x01,0xA0,0x0F,0xD8,
0x03,0xA0,0x08,0x18,0x03,0x60,0x00,0x18,0x03,0x40,0x00,0x18,0x03,0xC0,0x00,0x18,
0x03,0x80,0x00,0x18,0x03,0x00,0x00,0x18,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x10,
0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*1*/
"测",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x02,0x0C,0x10,0x08,0x07,0x1F,0xF8,0x04,0x03,0xBF,0xF0,0x02,0x01,0xBC,0x30,0x03,
0x03,0xEC,0x30,0x03,0x01,0x5C,0x60,0x03,0x00,0xD8,0x60,0x03,0x00,0xD8,0x60,0x03,
0x80,0x98,0x62,0x03,0x61,0xB8,0x43,0x07,0x71,0xB1,0x43,0x06,0x31,0x32,0x43,0x06,
0x33,0x76,0xC3,0x06,0x3A,0x64,0xC7,0x06,0x3E,0xEC,0xC0,0x06,0x3E,0x78,0xC0,0x06,
0x3C,0x30,0x40,0x06,0x7C,0x70,0x00,0x06,0x78,0xE0,0x60,0x06,0x7B,0xFF,0xF0,0x06,
0xF7,0xC0,0x00,0x06,0xE4,0x00,0x00,0x06,0x40,0x00,0x00,0x06,0x00,0x00,0x00,0x06,
0x00,0x00,0x00,0x7C,0x00,0x00,0x8F,0xF0,0x00,0x00,0x7C,0x00,0x00,0x00,0x00,0x00,/*2*/
"试",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x00,
0x00,0x00,0x7F,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0xC0,
0x00,0x00,0x00,0xCE,0x03,0x80,0x00,0xCF,0xFF,0xC0,0x00,0xDD,0x41,0x80,0x0F,0xFE,
0x00,0x07,0xFF,0xFC,0x00,0x0C,0x00,0xF0,0x00,0x18,0x0F,0xC0,0x3E,0x19,0xFF,0x40,
0xF3,0x11,0xBC,0x60,0x83,0x30,0x7F,0xE0,0x03,0xB1,0xFE,0x20,0x03,0x33,0x80,0x20,
0x03,0x70,0x00,0x30,0x03,0x60,0x00,0x10,0x03,0x60,0x00,0x18,0x07,0xC0,0x00,0x0C,
0x07,0xC0,0x00,0x04,0x07,0x80,0x00,0x02,0x01,0x00,0x00,0x03,0x00,0x00,0x00,0x01,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*3*/
};
  
#endif
