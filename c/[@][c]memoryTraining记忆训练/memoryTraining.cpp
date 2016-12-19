// memoryTraining.cpp : Defines the entry point for the console application.
//记忆训练
//于正洋
//inc@live.cn

#include "stdafx.h"
#include "time.h"
#include "math.h"
#include "windows.h"
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#define XXX 600	//游戏界面宽度
#define YYY 600	//游戏界面高度

int fang_temp[3];
#define TEMP_X fang_temp[0]
#define TEMP_Y fang_temp[1]
#define TEMP_R fang_temp[2]

int level = 0;	//当前关卡
int fang_group[100][3];	//存放方格的数组
int h_i=0;
int i = 0;
bool enableDo;	//表示此处理是无效处理，忽略此处理

double delay = 0;
#define DELAY for(delay=60000;delay>0;delay--);	//空循环做延时操作
#define OVER for(delay=60000000;delay>0;delay--);	//空循环做延时操作

//#define DELAY Sleep(1);	//毫秒做延时操作的时候不是很准确，在绘图时不同win系统有卡顿
//#define OVER Sleep(1);

#define FANG_X fang_group[h_i][0]
#define FANG_Y fang_group[h_i][1]
#define FANG_R fang_group[h_i][2]

MOUSEMSG m;		// 定义鼠标消息
//**************************************************
extern void painting();
extern void cg();
extern void over();
extern void determine();
extern void prompt();
extern void sleep(unsigned int mseconds);
extern void info();
//**************************************************
void main()
{
	// 初始化图形窗口
	initgraph(XXX,YYY);
	info();

	while(true)
	{
		m = GetMouseMsg();
		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:
				// 如果在按住Ctrl的时候单击鼠标左键
				if (m.mkCtrl)
				{
					prompt();//提示(即作弊)
					FlushMouseMsgBuffer();
				}
				else
				{
					determine();//正常点击时进入处理(看一下点击的是不是最后出现的格子)
					FlushMouseMsgBuffer();
				}
				break;
			//case WM_RBUTTONUP:
			//	return;	// 按鼠标右键退出程序
		}
	}

	// 关闭图形窗口
	closegraph();
}
//**************************************************

//绘图的方法
void painting()
{
	time_t seed = time(NULL);
	srand((unsigned int)seed);
	if( (rand() % 1) == 0)
	{
		TEMP_X = rand() % (XXX-20) +10;
		TEMP_Y = rand() % (YYY-20) +10;
	}
	else
	{
		TEMP_Y = rand() % (YYY-20) +10;
		TEMP_X = rand() % (XXX-20) +10;
	}
	TEMP_R = rand() % (20) +10;
	setcolor(WHITE);
	rectangle(TEMP_X - TEMP_R , TEMP_Y - TEMP_R , TEMP_X + TEMP_R , TEMP_Y + TEMP_R);
	h_i=level;

	FANG_X=TEMP_X;	//(横坐标)在这里把临时格子存入了所有格子的数组中
	FANG_Y=TEMP_Y;	//(纵坐标)
	FANG_R=TEMP_R;	//(半径)

	for(h_i = 1 ;  h_i < level ; h_i ++)
	{
		rectangle(FANG_X - FANG_R , FANG_Y - FANG_R , FANG_X + FANG_R , FANG_Y + FANG_R);
	}
}

//过场动画方法
void cg()
{				
	LOGFONT f;
	getfont(&f);                          // 获取当前字体设置
	f.lfHeight = 48;                      // 设置字体高度为 48
	strcpy(f.lfFaceName, "黑体");         // 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	setfont(&f);                          // 设置字体样式
	
	char message[17]="LEVEL ";
	char level_char[5];
	itoa(level , level_char , 10 );   
	strcat(message,level_char);
	strcat(message,"    ");

	for(i = 0;i <XXX;i++)
	{
		setcolor(WHITE);
		line(i,0,i,YYY);
		setcolor(WHITE);
		outtextxy(i-240,YYY/3,message);
		DELAY
	}

	for(i = 0;i <XXX;i++)
	{
		setcolor(BLACK);
		line(i,0,i,YYY);
		DELAY
	}
}

//游戏结束处理
void over()
{
	OVER
	setcolor(BLACK);
	rectangle(TEMP_X - TEMP_R , TEMP_Y - TEMP_R , TEMP_X + TEMP_R , TEMP_Y + TEMP_R);
	OVER
	setcolor(WHITE);
	rectangle(TEMP_X - TEMP_R , TEMP_Y - TEMP_R , TEMP_X + TEMP_R , TEMP_Y + TEMP_R);
	OVER
	setcolor(BLACK);
	rectangle(TEMP_X - TEMP_R , TEMP_Y - TEMP_R , TEMP_X + TEMP_R , TEMP_Y + TEMP_R);
	OVER
	setcolor(WHITE);
	rectangle(TEMP_X - TEMP_R , TEMP_Y - TEMP_R , TEMP_X + TEMP_R , TEMP_Y + TEMP_R);
	for(i = 0;i <XXX;i++)
	{
		setcolor(BLACK);
		line(i,0,i,YYY);
		DELAY
	}

	LOGFONT f;
	getfont(&f);                          // 获取当前字体设置
	f.lfHeight = 48;                      // 设置字体高度为 48
	strcpy(f.lfFaceName, "黑体");         // 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	setfont(&f);                          // 设置字体样式
	
	char message[17]="SCORE ";
	char level_char[5];
	itoa((level-1) , level_char , 10 );   
	strcat(message,level_char);
	strcat(message,"    ");
	setcolor(WHITE);

	for(i = 0;i <XXX;i++)
	{
		setcolor(WHITE);
		line(i,0,i,YYY);
		setcolor(WHITE);
		outtextxy(i-240,YYY/3,message);
		DELAY
	}

	level=0;
}

//正常处理流程
void determine()
{
	if(level > 0)
	{
		enableDo = false;
		for(h_i = 1 ;  h_i <= level ; h_i ++)
			if(abs(FANG_X-m.x) < FANG_R && abs(FANG_Y-m.y) < FANG_R)
			{
				enableDo = true;
				break;
			}
		if(!enableDo)
			return;
	}

	if(level==0)
	{
		level++;
		cg();
		painting();
	}
	else
	{
		if(abs(TEMP_X-m.x) < TEMP_R && abs(TEMP_Y-m.y) < TEMP_R )
		{
			level++;
			cg();
			painting();
		}
		else
		{
			over();
		}
	}
}

//提示(作弊)的方法
void prompt()
{
	OVER
	setcolor(BLACK);
	rectangle(TEMP_X - TEMP_R , TEMP_Y - TEMP_R , TEMP_X + TEMP_R , TEMP_Y + TEMP_R);
	OVER
	setcolor(WHITE);
	rectangle(TEMP_X - TEMP_R , TEMP_Y - TEMP_R , TEMP_X + TEMP_R , TEMP_Y + TEMP_R);
	OVER
	setcolor(BLACK);
	rectangle(TEMP_X - TEMP_R , TEMP_Y - TEMP_R , TEMP_X + TEMP_R , TEMP_Y + TEMP_R);
	OVER
	setcolor(WHITE);
	rectangle(TEMP_X - TEMP_R , TEMP_Y - TEMP_R , TEMP_X + TEMP_R , TEMP_Y + TEMP_R);
}
void info()
{
	LOGFONT f;
	getfont(&f);                          // 获取当前字体设置
	f.lfHeight = 48;                      // 设置字体高度为 48
	strcpy(f.lfFaceName, "黑体");         // 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	setfont(&f);                          // 设置字体样式

	setcolor(WHITE);
	outtextxy(240,200,"memoryTraining");

	f.lfHeight = 24;                      // 设置字体高度为 48
	setfont(&f);                          // 设置字体样式
	outtextxy(450,450,"inc@live.cn");

	f.lfHeight = 20;                      // 设置字体高度为 48
	setfont(&f);                          // 设置字体样式
	outtextxy(400,500,"于正洋");
}