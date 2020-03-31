#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

void delay(uint ms)//延迟函数，参数为毫秒
{
	uint i,j;
	for(i=0;i<ms;i++)
		for(j=123;j>0;j--);
}

//1.流水灯(D1到D8来回滚动点亮)
/*
#define led P2
void delay(unsigned int i)
{
	while(i--);
}
void main()
{
	unsigned int i;
	led =0x0a;
	while(1)
	{
		led=0xfe;
		for(i=0;i<7;i++)
		{
			led<<=1;
			led+=0x01;
			delay(65535);
		}
		led=0x7f;
		for(i=0;i<7;i++)
		{
			led>>=1;
			led=led+0x80;
			delay(65535);
		}
	}
}*/

//2.静态数码管(从0~9循环显示，间隔约1s)
/*
sbit ls138a=P2^2;
sbit ls138b=P2^3;
sbit ls138c=P2^4;
unsigned char code duanxuan[]=
{
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71
};
void main()
{
	unsigned char i;
	ls138a=0;
	ls138b=0;
	ls138c=0;
	for(i=0;i<10;i++)
	{
		P0=duanxuan[i];
		delay(1000);
	}
}*/

//3.动态数码管(8位数码管显示从0~f)
/*
sbit lsa=P2^2;
sbit lsb=P2^3;
sbit lsc=P2^4;
uchar code duanxuan[]=
{
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
	0x77,0x7c,0x39,0x5e,0x79,0x71
};
void main()
{
	uchar i;
	uint j;
	while(1)
	{
		for(j=0;j<17;j++)
		{
			for(i=80000;i>0;i--)
			{
				lsa=0;lsb=0;lsc=0;P0=duanxuan[j];delay(1);
				lsa=1;lsb=0;lsc=0;P0=duanxuan[j];delay(1);
				lsa=0;lsb=1;lsc=0;P0=duanxuan[j];delay(1);
				lsa=1;lsb=1;lsc=0;P0=duanxuan[j];delay(1);
				lsa=0;lsb=0;lsc=1;P0=duanxuan[j];delay(1);
				lsa=1;lsb=0;lsc=1;P0=duanxuan[j];delay(1);
				lsa=0;lsb=1;lsc=1;P0=duanxuan[j];delay(1);
				lsa=1;lsb=1;lsc=1;P0=duanxuan[j];delay(1);
			}
		}
	}
}*/

//4.独立按键+蜂鸣器(k1使数码管增加显示，k2减少显示，16进制,按键使蜂鸣器响)
/*
sbit key1=P3^1;
sbit key2=P3^0;
sbit lsa=P2^2;
sbit lsb=P2^3;
sbit lsc=P2^4;
sbit beep=P1^5;
uchar i=0;
uchar code duanxuan[]=
{
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
	0x77,0x7c,0x39,0x5e,0x79,0x71
};
void key()
{
	if(key1==0)
	{
		delay(5);
		if(key1==0)
		{
			if(i<15)
				i++;
			else i=0;
		}
		while(!key1)
		{
			beep=~beep;
			delay(50);
		}
	}
	else if(key2==0)
	{
		delay(5);
		if(key2==0)
		{
			if(i>0)
				i--;
			else i=15;
		}
		while(!key2)
		{
			beep=~beep;
			delay(50);
		}
	}
}
void main()
{
	lsa=0;
	lsb=0;
	lsc=0;
	while(1)
	{
		P0=duanxuan[i];
		key();
		delay(100);
	}
}*/

//5.LED点阵单列循环
/*
void main()
{
	uchar i;
	while(1)
	{
		P0=0x7f;
		for(i=0;i<8;i++)
		{
			delay(1000);
			P0=P0>>1;
			P0+=0x80;
		}
	}
}*/

//6.电机控制，数码管动态显示PWM
/*
sbit motor=P1^0;//ULN2003A驱动
sbit key1=P3^1;//独立键盘
sbit key2=P3^0;
sbit key3=P3^2;
sbit key4=P3^3;
sbit lsa=P2^2;//138编码器
sbit lsb=P2^3;
sbit lsc=P2^4;
#define top 10//PWM循环的最大值
uchar code duanxuan[]=		//0~9 + 0
{
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
	0x3f
};
uchar pwm=top;//全局变量，电机PWM
void display()//数码管显示十位，个位
{
	lsa=0;lsb=0;lsc=0;P0=duanxuan[pwm%10];P0=0x00;	//个位
	lsa=1;lsb=0;lsc=0;P0=duanxuan[pwm/10];P0=0x00;	//十位
	//lsa=0;lsb=1;lsc=0;P0=duanxuan[pwm/100];delay(1);//百位
}
void keycheck()
{
	if(key1==0)//加速
	{
		delay(5);
		if(key1==0)
		{
			if(pwm<top) pwm++;
		}
		while(!key1);
	}
	
	if(key2==0)//减速
	{
		delay(5);
		if(key2==0)
		{
			if(pwm>0) pwm--;
		}
		while(!key2);
	}
	
	if(key3==0)//停机
	{
		delay(5);
		if(key3==0)
		{
			pwm=0;
		}
		while(!key3);
	}
	
	if(key4==0)//全速
	{
		delay(5);
		if(key4==0)
		{
			pwm=top;
		}
		while(!key4);
	}
}
void main()
{
	uchar i;
	while(1)
	{
		for(i=pwm;i>0;i--)//motor start
		{
			motor=1;
			display();
			keycheck();
		}
		for(i=top-pwm;i>0;i--)//motor stop
		{
			motor=0;
			display();
			keycheck();
		}
	}
}
*/

//7.外部中断0和1，控制灯
/*
sbit key3=P3^2;
sbit key4=P3^3;
#define led P2
void main()
{
	EA=1;//总开关
	EX0=1;//启用外部中断
	EX1=1;
	IT0=1;//设置模式
	IT1=1;
	P2=0x00;
	while(1) led=0x00;
}
void it0() interrupt 0
{
			led=0xff;
			delay(2000);
}
void it1() interrupt 2
{
	uchar i;
	led=0xfe;
	for(i=0;i<7;i++)
	{
		led<<=1;
		led+=0x01;
		delay(1000);
	}
	led=0x7f;
	for(i=0;i<7;i++)
	{
		led>>=1;
		led=led+0x80;
		delay(1000);
	}
}*/

//8.定时器中断0，外部中断1，数码管计时60s，按键4清零
/*
sbit lsa=P2^2;//138编码器
sbit lsb=P2^3;
sbit lsc=P2^4;
uchar num=0,i=1;
uchar code duanxuan[]=		//0~9
{
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
};
void display()
{
	lsa=0;lsb=0;lsc=0;P0=duanxuan[i%10];P0=0x00;	//个位
	lsa=1;lsb=0;lsc=0;P0=duanxuan[i/10];P0=0x00;	//十位
}
void main()
{
	EA=1;
	ET0=1;
	TMOD|=0x01;
	TH0=0X3C;
	TL0=0XB0;
	TR0=1;
	EX1=1;
	IT1=1;
	while(1)
	{
		if(num==20)
		{
			i++;
			num=0;
		}
		if(i==61) i=1;
		display();
	}
}
void key4() interrupt 2		//外部中断1,计数清零
{
	i=1;
}
void time0() interrupt 1	//T0定时器中断,50ms
{
	TH0=0X3C;
	TL0=0XB0;
	num++;
}*/

//9.秒表
/*
sbit lsa=P2^2;//74HC138编码器，使能控制LLH，定义输入端口
sbit lsb=P2^3;
sbit lsc=P2^4;
uchar hour,min,sec,ssec,i;//i用于记循环次数
bit flag=1;								//flag为启停标志
uchar code duanxuan[]=		//共阴数码管0~9数字编码
{
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
};
//数码管显示函数
void display()
{
	lsa=0;lsb=0;lsc=0;P0=duanxuan[ssec];P0=0x00;
	lsa=1;lsb=0;lsc=0;P0=duanxuan[sec%10]+0x80;P0=0x00;	//加上小数点
	lsa=0;lsb=1;lsc=0;P0=duanxuan[sec/10];P0=0x00;
	lsa=1;lsb=1;lsc=0;P0=0x40;P0=0x00;P0=0x00;					//短横线
	lsa=0;lsb=0;lsc=1;P0=duanxuan[min%10];P0=0x00;
	lsa=1;lsb=0;lsc=1;P0=duanxuan[min/10];P0=0x00;
	lsa=0;lsb=1;lsc=1;P0=0x40;P0=0x00;
	lsa=1;lsb=1;lsc=1;P0=duanxuan[hour];P0=0x00;
}
//主控函数
void main()
{
	EA=1;				//中断允许总开关
	ET0=1;			//定时器0中断打开
	TMOD|=0x01;	//工作方式1，16位定时器，启停仅受TR0控制
	TH0=0X3C;		//50ms中断计时，填入初值
	TL0=0XB0;
	TR0=1;			//启动定时器0
	EX0=1;			//外部中断0打开
	IT0=1;			//下降沿触发
	EX1=1;			//外部中断1打开
	IT1=1;
	while(1)
	{
		if(i>=2)
		{
			i=0;				//每0.1s清零计数一次
			if(flag==1)	//flag为1表示启动
			{
				ssec++;
				if(ssec==10)
				{
					ssec=0;
					sec++;
				}
				if(sec==60)
				{
					sec=0;
					min++;
				}
				if(min==60)
				{
					min=0;
					hour++;
				}
				if(hour>=10) hour=0;
			}
		}
		display();
	}
}
//定时器中断0,50ms中断计时
void time() interrupt 1
{
	TH0=0X3C;
	TL0=0XB0;
	i++;
}
//外部中断0,暂停或继续,k3，P3^2口	
void stop() interrupt 0
{
	flag=~flag;
}
//外部中断1,重新计时,k4,P3^3口
void restart() interrupt 2
{
	hour=0;
	min=0;
	sec=0;
	ssec=0;
	flag=0;	//重新计时后先暂停
}*/

//10.蓝牙串口通信,数码管显示
/*
uchar a;
sbit lsa=P2^2;//74HC138编码器，使能控制LLH，定义输入端口
sbit lsb=P2^3;
sbit lsc=P2^4;
uchar code duanxuan[]=		//0~9 E
{
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
	0x79
};
void Init()
{
  SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=0XF3;				//计数器初始值设置，注意波特率是4800的
	TL1=0XF3;
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;					//打开计数器
}
void display()
{
	if(a>0x30&&a<=0x39)
	{
		lsa=0;lsb=0;lsc=0;P0=duanxuan[a-48];
	}
	else
	{
		lsa=0;lsb=0;lsc=0;P0=duanxuan[10];
	}
}
void main () 
{
	Init();//初始化
//	P2=0x7f;
	while(1)
	{
		display();
	}
} 
void Com_Int(void) interrupt 4
{
	a = SBUF;
	RI = 0; 		//清除接收中断标志位
	SBUF=a;
	while(!TI);	//等待发送数据完成
	TI=0;				//清除发送完成标志位
//	if(P2<=0xfd)
//	{
//		P2>>=1;
//		P2+=0x80;
//	}
//	else
//	{
//		P2=0x7f;
//	}
}
*/
