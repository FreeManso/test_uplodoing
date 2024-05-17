#include "modbus.h"
#include "stdio.h"
#include "user_def.h"
#include "crc.h"
#include "string.h"
#include "adc.h"

extern uint8_t Modbus_Slave_Addr;
extern UART_HandleTypeDef huart1;
uint8_t modbus_send[XUART1_Buf_Len]={0};
//void //XSEND_Motor_Ctr(X_MTCTR_t ctr,X_Motor_t motor,float pos,uint8_t spd);
typedef  int32_t (*modbus_dispose)(X_Modbus_Order_t *order,uint32_t flash);

extern uint16_t DMA_TATA_BUFFER[CONVERT_DMA_DATA];
/**
  * @brief 与PC通信指令格式。
  */
typedef struct
{
	uint16_t addr;	//地址
	uint8_t func;		//功能码
	uint16_t len;		//寄存器数量
	uint32_t flash;		//flash存储地址
	modbus_dispose dispose;//处理函数
}MODBUS_t;


uint32_t modbus_last_rng = 0; //最后一次读的随机值

uint32_t modbus_system_status = 0;



uint16_t modbus_stutas_deytime = 100;
void modbus_init(void)
{
	modbus_system_status = 0;
	modbus_last_rng = 0;
	//modbus_init_motor();
	modbus_init_stdeytime();
}



void modbus_init_stdeytime(void)
{
	if(modbus_stutas_deytime > 10000)
		modbus_stutas_deytime = 100;
	if(modbus_stutas_deytime < 10)
		modbus_stutas_deytime = 100;
}

//设置状态位入口 set=0为置0 其余置1
void modbus_setstatus(uint32_t bit,X_BITSET_t set)
{
	if(set)
	{
		modbus_system_status |= bit;	
	}
	else
	{
		modbus_system_status &= ~bit; 
	}
}
//
X_BITSET_t modbus_getstatus(uint32_t bit )
{
	if(modbus_system_status & bit)
	{
		return 	MODBUS_BIT_SET;
	}
	else
	{
		return 	MODBUS_BIT_CLI;
	}
}

//通过DMA中断方式发送
int32_t modbus_send_data(X_Modbus_Order_t *order)
{
		if(order->func == 3)
		{
			HAL_Delay(1);
			uint8_t read_len = order->len*2;
			modbus_send[0] = Modbus_Slave_Addr;
			modbus_send[1] = order->func;
			modbus_send[2] = read_len;
			memcpy(modbus_send+3,(uint8_t *)order->val,read_len);	
			uint16_t crc = modbuscrc16(modbus_send,3+read_len);
			modbus_send[3+read_len] = crc/256;
			modbus_send[3+read_len+1] = crc%256;
			
			if(HAL_UART_Transmit_DMA(&huart1,modbus_send,read_len+5) != HAL_OK)
			{
				
			}
		}
		else if( order->func == 6)
		{

			HAL_Delay(1);
			modbus_send[0] = Modbus_Slave_Addr;
			modbus_send[1] = order->func;
			
			modbus_send[2] = order->addr>>8;
			modbus_send[3] = order->addr & 0xff;
			
			modbus_send[4] = order->val[0];
			modbus_send[5] = order->val[1];
			uint16_t crc = modbuscrc16(modbus_send,6);
			modbus_send[6] = crc/256;
			modbus_send[7] = crc%256;
			
			if(HAL_UART_Transmit_DMA(&huart1,modbus_send,8) != HAL_OK)
			{
				
			}
		}
		else if( order->func == 16)
		{
		
			HAL_Delay(1);
			modbus_send[0] = Modbus_Slave_Addr;
			modbus_send[1] = order->func;
			
			modbus_send[2] = order->addr>>8;
			modbus_send[3] = order->addr & 0xff;
			
			modbus_send[4] = order->len>>8;
			modbus_send[5] = order->len & 0xff;
			uint16_t crc = modbuscrc16(modbus_send,6);
			modbus_send[6] = crc/256;
			modbus_send[7] = crc%256;
			
			if(HAL_UART_Transmit_DMA(&huart1,modbus_send,8)!= HAL_OK)
			{
				
			}
		}
		return 0;
}



//读取系统状态
int32_t message_callback_readstatus(X_Modbus_Order_t *order,uint32_t flash)
{
	X_Set_Order_RunStart(1);
	order->val[2] = (modbus_system_status>>24)&0xff;
	order->val[3] = (modbus_system_status>>16)&0xff;
	order->val[0] = (modbus_system_status>>8)&0xff;
	order->val[1] = modbus_system_status&0xff;
	modbus_send_data(order);
	return 1;
}

//读取软件版本号
int32_t message_callback_readsoftware(X_Modbus_Order_t *order,uint32_t flash)
{
	X_Set_Order_RunStart(1);

	order->val[0] = (software_version_big&0xff00)>>8;
	order->val[1] = software_version_big&0xff;
	
	order->val[2] = (software_version_sml&0xff00)>>8;
	order->val[3] = software_version_sml&0xff;
			
	modbus_send_data(order);
	return 1;
}

//读取硬件版本号
int32_t message_callback_readhardware(X_Modbus_Order_t *order,uint32_t flash)
{
	X_Set_Order_RunStart(1);

	order->val[0] = (hardware_version_big&0xff00)>>8;
	order->val[1] = hardware_version_big&0xff;
	
	order->val[2] = (hardware_version_sml&0xff00)>>8;
	order->val[3] = hardware_version_sml&0xff;
			
	modbus_send_data(order);
	return 1;
}

//读检测距离
int32_t message_callback_read_ditance(X_Modbus_Order_t *order,uint32_t flash)
{
	X_Set_Order_RunStart(1);
	
	for(uint8_t i=0;i<6;i++)
	{
		order->val[0+(1*2)] = (DMA_TATA_BUFFER[i]&0xff00)>>8;
		order->val[1+(1*2)] = DMA_TATA_BUFFER[i]&0xff;;
	}
	modbus_send_data(order);
	return 1;
}


const MODBUS_t message_list[] = {\

	{30196,	3,	16,	   0,		message_callback_readsoftware},
	{30228,	3,	16,	   0,		message_callback_readhardware},	
	
	{30333, 3,  6,     0,       message_callback_read_ditance},
};

//MODBUS消息处理分发
//
void modbus_message_dispose(X_Modbus_Order_t *order)
{
	//int32_t ret = 0;
	uint8_t find_addr = 0;
	uint16_t message_num = sizeof(message_list)/sizeof(MODBUS_t);
	for(int i=0;i<message_num;i++)
	{
		if(order->addr == message_list[i].addr) //地址匹配
		{
			if(order->addr != 30990)
				modbus_setstatus(STATUS_15_ERRADDN,MODBUS_BIT_CLI);
			find_addr = 1;
			//Lcd_Clear_Area(48,0,80,16,0xffff);
			//LCD_SHOWNUM(48,0,order->addr,0x0000);
			if(message_list[i].func == order->func)
			{
				if(message_list[i].len >= order->len)//寄存器数量匹配
				{
					if(message_list[i].dispose != NULL)
					{
						
						//HAL_GPIO_WritePin(OD_IDLE_GPIO_Port,OD_IDLE_Pin,GPIO_PIN_SET);//收到指令将信号输出置位
						 message_list[i].dispose(order,message_list[i].flash);
					}
				}
				else
					;
			}
			break;
		}
		/*
		else if((order->addr>message_list[i].addr)&&((order->addr<=(message_list[i].addr+message_list[i].len)))
		{
			if(order->addr != 30990)
				modbus_setstatus(STATUS_15_ERRADDN,MODBUS_BIT_CLI);
			find_addr = 1;
			if(message_list[i].func == order->func)
			{
				if((message_list[i].addr+message_list[i].len-order->addr)>= order->len)//寄存器数量匹配
				{
					if(message_list[i].dispose != NULL)
					{
						ret = message_list[i].dispose(order,message_list[i].flash);
					}
				}
				else
					ret = 0;
			}
			break;
		}
		*/
	}
	
	if(find_addr == 0) 	//未发现匹配地址
	{
		modbus_setstatus(STATUS_15_ERRADDN,MODBUS_BIT_SET);

	}


}





/**************************************************************************************************/
/**************************************************************************************************/
void X_Set_Order_RunStart(int mode)   //启动软件定时器
{
	
	/*****************************************************************************/
	//HAL_GPIO_WritePin(OD_IDLE_GPIO_Port,OD_IDLE_Pin,GPIO_PIN_RESET);
	/*****************************************************************************/
//	HAL_GPIO_WritePin(SYS_STATE_GPIO_Port,SYS_STATE_Pin,GPIO_PIN_RESET);

	if((mode == 1) && (modbus_getstatus(STATUS_00_ORDERT) == MODBUS_BIT_CLI)) //
	{
//		osTimerStart(XTIMERHandle,modbus_stutas_deytime); //
	}
	else
	{         
		modbus_setstatus(STATUS_00_ORDERT,MODBUS_BIT_SET);//指令状态

	}
}

void X_Set_Order_Runover(int mode)
{
	modbus_setstatus(STATUS_00_ORDERT,MODBUS_BIT_CLI);////指令状态
	/**************************************************************/
//	osTimerStart(XTIMERHandle,modbus_stutas_deytime); //
//    
    /*******************************************************************/
}








