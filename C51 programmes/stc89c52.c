#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

void delay(uint ms)//�ӳٺ���������Ϊ����
{
	uint i,j;
	for(i=0;i<ms;i++)
		for(j=123;j>0;j--);
}

//1.��ˮ��(D1��D8���ع�������)
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

//2.��̬�����(��0~9ѭ����ʾ�����Լ1s)
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

//3.��̬�����(8λ�������ʾ��0~f)
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

//4.��������+������(k1ʹ�����������ʾ��k2������ʾ��16����,����ʹ��������)
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

//5.LED������ѭ��
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

//6.������ƣ�����ܶ�̬��ʾPWM
/*
sbit motor=P1^0;//ULN2003A����
sbit key1=P3^1;//��������
sbit key2=P3^0;
sbit key3=P3^2;
sbit key4=P3^3;
sbit lsa=P2^2;//138������
sbit lsb=P2^3;
sbit lsc=P2^4;
#define top 10//PWMѭ�������ֵ
uchar code duanxuan[]=		//0~9 + 0
{
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
	0x3f
};
uchar pwm=top;//ȫ�ֱ��������PWM
void display()//�������ʾʮλ����λ
{
	lsa=0;lsb=0;lsc=0;P0=duanxuan[pwm%10];P0=0x00;	//��λ
	lsa=1;lsb=0;lsc=0;P0=duanxuan[pwm/10];P0=0x00;	//ʮλ
	//lsa=0;lsb=1;lsc=0;P0=duanxuan[pwm/100];delay(1);//��λ
}
void keycheck()
{
	if(key1==0)//����
	{
		delay(5);
		if(key1==0)
		{
			if(pwm<top) pwm++;
		}
		while(!key1);
	}
	
	if(key2==0)//����
	{
		delay(5);
		if(key2==0)
		{
			if(pwm>0) pwm--;
		}
		while(!key2);
	}
	
	if(key3==0)//ͣ��
	{
		delay(5);
		if(key3==0)
		{
			pwm=0;
		}
		while(!key3);
	}
	
	if(key4==0)//ȫ��
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

//7.�ⲿ�ж�0��1�����Ƶ�
/*
sbit key3=P3^2;
sbit key4=P3^3;
#define led P2
void main()
{
	EA=1;//�ܿ���
	EX0=1;//�����ⲿ�ж�
	EX1=1;
	IT0=1;//����ģʽ
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

//8.��ʱ���ж�0���ⲿ�ж�1������ܼ�ʱ60s������4����
/*
sbit lsa=P2^2;//138������
sbit lsb=P2^3;
sbit lsc=P2^4;
uchar num=0,i=1;
uchar code duanxuan[]=		//0~9
{
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
};
void display()
{
	lsa=0;lsb=0;lsc=0;P0=duanxuan[i%10];P0=0x00;	//��λ
	lsa=1;lsb=0;lsc=0;P0=duanxuan[i/10];P0=0x00;	//ʮλ
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
void key4() interrupt 2		//�ⲿ�ж�1,��������
{
	i=1;
}
void time0() interrupt 1	//T0��ʱ���ж�,50ms
{
	TH0=0X3C;
	TL0=0XB0;
	num++;
}*/

//9.���
/*
sbit lsa=P2^2;//74HC138��������ʹ�ܿ���LLH����������˿�
sbit lsb=P2^3;
sbit lsc=P2^4;
uchar hour,min,sec,ssec,i;//i���ڼ�ѭ������
bit flag=1;								//flagΪ��ͣ��־
uchar code duanxuan[]=		//���������0~9���ֱ���
{
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
};
//�������ʾ����
void display()
{
	lsa=0;lsb=0;lsc=0;P0=duanxuan[ssec];P0=0x00;
	lsa=1;lsb=0;lsc=0;P0=duanxuan[sec%10]+0x80;P0=0x00;	//����С����
	lsa=0;lsb=1;lsc=0;P0=duanxuan[sec/10];P0=0x00;
	lsa=1;lsb=1;lsc=0;P0=0x40;P0=0x00;P0=0x00;					//�̺���
	lsa=0;lsb=0;lsc=1;P0=duanxuan[min%10];P0=0x00;
	lsa=1;lsb=0;lsc=1;P0=duanxuan[min/10];P0=0x00;
	lsa=0;lsb=1;lsc=1;P0=0x40;P0=0x00;
	lsa=1;lsb=1;lsc=1;P0=duanxuan[hour];P0=0x00;
}
//���غ���
void main()
{
	EA=1;				//�ж������ܿ���
	ET0=1;			//��ʱ��0�жϴ�
	TMOD|=0x01;	//������ʽ1��16λ��ʱ������ͣ����TR0����
	TH0=0X3C;		//50ms�жϼ�ʱ�������ֵ
	TL0=0XB0;
	TR0=1;			//������ʱ��0
	EX0=1;			//�ⲿ�ж�0��
	IT0=1;			//�½��ش���
	EX1=1;			//�ⲿ�ж�1��
	IT1=1;
	while(1)
	{
		if(i>=2)
		{
			i=0;				//ÿ0.1s�������һ��
			if(flag==1)	//flagΪ1��ʾ����
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
//��ʱ���ж�0,50ms�жϼ�ʱ
void time() interrupt 1
{
	TH0=0X3C;
	TL0=0XB0;
	i++;
}
//�ⲿ�ж�0,��ͣ�����,k3��P3^2��	
void stop() interrupt 0
{
	flag=~flag;
}
//�ⲿ�ж�1,���¼�ʱ,k4,P3^3��
void restart() interrupt 2
{
	hour=0;
	min=0;
	sec=0;
	ssec=0;
	flag=0;	//���¼�ʱ������ͣ
}*/

//10.��������ͨ��,�������ʾ
/*
uchar a;
sbit lsa=P2^2;//74HC138��������ʹ�ܿ���LLH����������˿�
sbit lsb=P2^3;
sbit lsc=P2^4;
uchar code duanxuan[]=		//0~9 E
{
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
	0x79
};
void Init()
{
  SCON=0X50;			//����Ϊ������ʽ1
	TMOD=0X20;			//���ü�����������ʽ2
	PCON=0X80;			//�����ʼӱ�
	TH1=0XF3;				//��������ʼֵ���ã�ע�Ⲩ������4800��
	TL1=0XF3;
	ES=1;						//�򿪽����ж�
	EA=1;						//�����ж�
	TR1=1;					//�򿪼�����
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
	Init();//��ʼ��
//	P2=0x7f;
	while(1)
	{
		display();
	}
} 
void Com_Int(void) interrupt 4
{
	a = SBUF;
	RI = 0; 		//��������жϱ�־λ
	SBUF=a;
	while(!TI);	//�ȴ������������
	TI=0;				//���������ɱ�־λ
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
