// memoryTraining.cpp : Defines the entry point for the console application.
//����ѵ��
//������
//inc@live.cn

#include "stdafx.h"
#include "time.h"
#include "math.h"
#include "windows.h"
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#define XXX 600	//��Ϸ������
#define YYY 600	//��Ϸ����߶�

int fang_temp[3];
#define TEMP_X fang_temp[0]
#define TEMP_Y fang_temp[1]
#define TEMP_R fang_temp[2]

int level = 0;	//��ǰ�ؿ�
int fang_group[100][3];	//��ŷ��������
int h_i=0;
int i = 0;
bool enableDo;	//��ʾ�˴�������Ч�������Դ˴���

double delay = 0;
#define DELAY for(delay=60000;delay>0;delay--);	//��ѭ������ʱ����
#define OVER for(delay=60000000;delay>0;delay--);	//��ѭ������ʱ����

//#define DELAY Sleep(1);	//��������ʱ������ʱ���Ǻ�׼ȷ���ڻ�ͼʱ��ͬwinϵͳ�п���
//#define OVER Sleep(1);

#define FANG_X fang_group[h_i][0]
#define FANG_Y fang_group[h_i][1]
#define FANG_R fang_group[h_i][2]

MOUSEMSG m;		// ���������Ϣ
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
	// ��ʼ��ͼ�δ���
	initgraph(XXX,YYY);
	info();

	while(true)
	{
		m = GetMouseMsg();
		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:
				// ����ڰ�סCtrl��ʱ�򵥻�������
				if (m.mkCtrl)
				{
					prompt();//��ʾ(������)
					FlushMouseMsgBuffer();
				}
				else
				{
					determine();//�������ʱ���봦��(��һ�µ�����ǲ��������ֵĸ���)
					FlushMouseMsgBuffer();
				}
				break;
			//case WM_RBUTTONUP:
			//	return;	// ������Ҽ��˳�����
		}
	}

	// �ر�ͼ�δ���
	closegraph();
}
//**************************************************

//��ͼ�ķ���
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

	FANG_X=TEMP_X;	//(������)���������ʱ���Ӵ��������и��ӵ�������
	FANG_Y=TEMP_Y;	//(������)
	FANG_R=TEMP_R;	//(�뾶)

	for(h_i = 1 ;  h_i < level ; h_i ++)
	{
		rectangle(FANG_X - FANG_R , FANG_Y - FANG_R , FANG_X + FANG_R , FANG_Y + FANG_R);
	}
}

//������������
void cg()
{				
	LOGFONT f;
	getfont(&f);                          // ��ȡ��ǰ��������
	f.lfHeight = 48;                      // ��������߶�Ϊ 48
	strcpy(f.lfFaceName, "����");         // ��������Ϊ�����塱
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	setfont(&f);                          // ����������ʽ
	
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

//��Ϸ��������
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
	getfont(&f);                          // ��ȡ��ǰ��������
	f.lfHeight = 48;                      // ��������߶�Ϊ 48
	strcpy(f.lfFaceName, "����");         // ��������Ϊ�����塱
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	setfont(&f);                          // ����������ʽ
	
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

//������������
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

//��ʾ(����)�ķ���
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
	getfont(&f);                          // ��ȡ��ǰ��������
	f.lfHeight = 48;                      // ��������߶�Ϊ 48
	strcpy(f.lfFaceName, "����");         // ��������Ϊ�����塱
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	setfont(&f);                          // ����������ʽ

	setcolor(WHITE);
	outtextxy(240,200,"memoryTraining");

	f.lfHeight = 24;                      // ��������߶�Ϊ 48
	setfont(&f);                          // ����������ʽ
	outtextxy(450,450,"inc@live.cn");

	f.lfHeight = 20;                      // ��������߶�Ϊ 48
	setfont(&f);                          // ����������ʽ
	outtextxy(400,500,"������");
}