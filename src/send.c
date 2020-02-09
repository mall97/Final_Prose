#include "stm32f10x.h"
#include "stm32f10x_can.h"
#include <math.h>
#include "send.h"


int Lux[8];
int angulo, maximo, flag=0, last_ang=0;
extern uint16_t ADC1_Addr[8];



int vizinho(int pos, int v[8], int *pos2)
{
	if (pos == 7)
	{
		if (v[pos - 1] > v[0])
		{
			*pos2 = pos - 1;
			return v[pos - 1];
		}
		else
		{
			*pos2 = 0;
			return v[0];
		}
	}
	else
	{

		if (v[pos - 1] > v[pos + 1])
		{
			*pos2 = pos - 1;
			return v[pos - 1];
		}
		else
		{
			*pos2 = pos + 1;
			return v[pos + 1];
		}
	}
}

int roll(int max, int max2, int pos, int pos2, int angl[8])
{
	int ang;
	if (pos > pos2)
	{


			if(pos==7 && pos2==0)
			{
				ang = angl[pos] + (0.1225 * (max - max2));
			}
			else
			{
			ang = angl[pos] - (0.1225*(max - max2));
			}

		return ang;
	}
	else if (pos2 > pos)
	{

			if(pos2==7 && pos==0)
			{
			ang = angl[pos2] + (0.1225 * (max - max2));
			}
			else
			{
			ang = angl[pos] + (0.1225 * (max - max2));   // 45/400
			}

		return ang;
	}
}
/*
int roll(int max, int max2, int pos, int pos2, int angl[8])
{
	int ang;
	if(pos==0 && pos2==7)
	{
		ang=(8*45*max+7*45*max2)/(max+max2);
	}
	else if(pos==7 && pos2==0)
	{
		ang=(7*45*max+8*45*max2)/(max+max2);
	}
	else
	{
		ang=(pos*45*max+pos2*45*max2)/(max+max2);
	}
	return ang;
}
*/

void prose()
{	CanRxMsg RxMessage;

		if( CAN_MessagePending(CAN1,CAN_FIFO0)!=0)
		{
			CAN_Receive(CAN1, 0 ,&RxMessage);
			if(RxMessage.StdId==0x01)
				{

					if(angulo<0)
					{
						angulo=0;
					}
					CanTxMsg TxMessage;
					TxMessage.StdId = 0x01;			//identifier
					TxMessage.ExtId = 0x00;			//extended identifier
					TxMessage.IDE = CAN_ID_STD;		//type of identifier
					TxMessage.RTR = CAN_RTR_DATA;	//type of frame for message
					TxMessage.DLC =4;				//length of frame

					TxMessage.Data[0] = angulo >> 8;   //information to be transmitted, size of vector->8
					TxMessage.Data[1] = angulo & 0x00ff;
					TxMessage.Data[2] = maximo >>8;
					TxMessage.Data[3] = maximo & 0x00ff;


					CAN_Transmit(CAN1, &TxMessage);		//send information
					RxMessage.StdId=0;
					RxMessage.Data[0]=0x30;
				}
			else if(RxMessage.StdId==0x10)
			{
					flag=1;
					last_ang=angulo;
			}
	}

}

void calc()
{
	for(int i=0;i<8;i++)
	{
		float volt=3.3-(3.3*ADC1_Addr[i])/4096;
		float volt_1k=3.3-volt;
		float I=1000/volt_1k;
		Lux[i]=4000000*(pow(volt*I,-1.303));
	}

	int angl[8] = { 0, 45, 90, 135, 180, 225, 270, 315 };
	int max = 0, pos = 0, max2 = 0, pos2 = 0, ang=0;

	for (int i = 0; i < 8; i++)
	{
		if (Lux[i] > max)
		{
			max = Lux[i];
			pos = i;
		}
	}

	switch (pos)
	{
	case(0):
		max2 = vizinho(pos, Lux, &pos2);
		ang = roll(max, max2, pos, pos2, angl);
		break;
	case(1):
		max2 = vizinho(pos, Lux, &pos2);
		ang = roll(max, max2, pos, pos2, angl);
		break;
	case(2):
		max2 = vizinho(pos, Lux, &pos2);
		ang = roll(max, max2, pos, pos2, angl);
		break;
	case(3):
		max2 = vizinho(pos, Lux, &pos2);
		ang = roll(max, max2, pos, pos2, angl);
		break;
	case(4):
		max2 = vizinho(pos, Lux, &pos2);
		ang = roll(max, max2, pos, pos2, angl);
		break;
	case(5):
		max2 = vizinho(pos, Lux, &pos2);
		ang = roll(max, max2, pos, pos2, angl);
		break;
	case(6):
		max2 = vizinho(pos, Lux, &pos2);
		ang = roll(max, max2, pos, pos2, angl);
		break;
	case(7):
		max2 = vizinho(pos, Lux, &pos2);
		ang = roll(max, max2, pos, pos2, angl);
		break;

	}

	if(flag==0)
	{
	angulo=ang;
	}
	else
	{
		if(ang>last_ang)
		{
		angulo=ang-last_ang;
		}
		else
		{
		angulo=ang+last_ang;
		}
	}

	maximo=max;
}
