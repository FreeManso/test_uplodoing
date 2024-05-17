/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "user_def.h"
#include "AT_Order.h"
#include "usart_dispose.h"
#include "crc.h"
/* USER CODE BEGIN 0 */

/*串口DMA接收环形缓冲*/

uint8_t XUART1_Buf[XUART1_Buf_Len];
uint16_t XUART1_Writ_p = 0;
uint16_t XUART1_Read_p = 0;
/**/
uint8_t XUART2_Buf[XUART2_Buf_Len];
uint16_t XUART2_Writ_p = 0;
uint16_t XUART2_Read_p = 0;

uint8_t XUART3_Buf[XUART3_Buf_Len];
uint16_t XUART3_Writ_p = 0;
uint16_t XUART3_Read_p = 0;


uint8_t Modbus_Slave_Addr = 0x94 ; //磁吸0x90 震荡 0x92

/* USER CODE END 0 */


extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;


//extern UART_HandleTypeDef huart2;
//extern DMA_HandleTypeDef hdma_usart2_rx;
//extern DMA_HandleTypeDef hdma_usart2_tx;


/* USER CODE BEGIN 1 */
/*开启串口空闲中断和DMA接收中断*/
void X_Start_IDLE_DMA(void)
{	
	Modbus_Slave_Addr = 0x94;
	HAL_UART_Receive_DMA(&huart1,XUART1_Buf,XUART1_Buf_Len);
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
	
//    HAL_UART_Receive_DMA(&huart2,XUART2_Buf,XUART2_Buf_Len);
//	__HAL_UART_ENABLE_IT(&huart2,UART_IT_IDLE);
	
}
/*获取DMA缓冲中的新数据，返回新数据长度，0表示没有新数据*/
uint16_t X_UART1_Get_NewBuf(uint8_t *buf)
{
	uint16_t len=0;
	if(XUART1_Writ_p == XUART1_Buf_Len)
		XUART1_Writ_p = 0;

	while(XUART1_Writ_p != XUART1_Read_p)
	{
		buf[len++] = XUART1_Buf[XUART1_Read_p];
		XUART1_Buf[XUART1_Read_p] = 0;
		XUART1_Read_p++;
		if(XUART1_Read_p >= XUART1_Buf_Len)
			XUART1_Read_p = 0;
		if(len >= XUART1_Buf_Len)
			break;
	}
	if(READ_BIT(huart1.Instance->CR3, USART_CR3_DMAR) == DISABLE)//防止DMA挂掉
	{
			__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
			HAL_UART_Receive_DMA(&huart1,XUART1_Buf,XUART1_Buf_Len);
	}

	return len;
}


/*串口空闲中断处理函数 ，更新新数据缓冲终点*/
void X_Uart_IDLE_IT_Dispose()
{
	if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE) != RESET)
	{
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
		XUART1_Writ_p = XUART1_Buf_Len - __HAL_DMA_GET_COUNTER(huart1.hdmarx);
		
	}
}

#if 0
//分析查找合法包
uint8_t X_Uart1_Analyze(uint8_t *recvbuf,X_Order_t *order)
{

	static uint16_t anay = 0;//缓冲区空闲位置
	uint8_t ret = 0;
	uint16_t head = 0xffff,end = 0xffff;//标记当前循环是否找到 包头位置 包尾位置 合法包
	uint16_t len = X_UART1_Get_NewBuf(recvbuf+anay);
	anay+=len;
	if(READ_BIT(huart1.Instance->CR3, USART_CR3_DMAR) == DISABLE)//防止DMA挂掉
	{
		__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
		HAL_UART_Receive_DMA(&huart1,XUART1_Buf,XUART1_Buf_Len);

	}
	if(anay>12)
	{
		head = X_Search_Head(recvbuf,anay); //尝试查找包头
		if(head < anay) //说明找到包头
		{
			if((anay - head) > 12) //完整包的最少长度
			{
				order->order = recvbuf[head+4];
				order->len = recvbuf[head+5];
				end = head+11+order->len;
				if(anay>end)
				{
					if((recvbuf[end] == 0x5A)&&(recvbuf[end-1] == 0x5A)&&(recvbuf[end-2] == 0x5A)&&(recvbuf[end-3] == 0x5A))//判断是不是包尾
					{
						uint16_t order_crc = recvbuf[end-5]+recvbuf[end-4]*256;
						uint16_t cal_crc =GetCrc16(recvbuf+head+4,2+order->len);//验证CRC
						if(order_crc == cal_crc)//找到合法包
						{
							if(order->len < XUART_Order_Len)
							{
								memcpy(order->cont,recvbuf+head+6,order->len);
							}
							ret = 1;
							//xQueueSend(XRECV_OrderHandle, &order, 10 / portTICK_PERIOD_MS); //发送命令包到另外一个线程处理
							
						}
						else
						{
						//	XUART_REPLY_Order_Status(1); //CRC出错
						//	if(order.len < XUART_Order_Len)
							{
						//		memcpy(order.cont,recvbuf+head+7,order.len);
							}
						//	xQueueSend(XRECV_OrderHandle, &order, 10 / portTICK_PERIOD_MS); //不CRC测试用 
						}
						
						end+=1;//指到结束包的后一个字节
						for(int i=0;i<(anay-end);i++) //把包从当前缓冲中去掉。
						{
							recvbuf[i] = recvbuf[i+end];
						}
						anay-=end;
					}
					else //指定位置不是包尾，可能找到的包头不是真的包头，或者当前这个包丢数据了，只能把包头丢弃，重新找下一个包
					{
						for(int i=0;i<(anay-(head+4));i++)
						{
							recvbuf[i] = recvbuf[i+(head+4)];
						}
						anay-=(head+4);
					}
				}
			}
		}
		else if(anay >= 4) //大于5个字节且没找到包头，说明这五个字节无用，去掉第一个字节
		{
			for(int i=0;i<(anay-1);i++)
			{
				recvbuf[i] = recvbuf[i+1];
			}
			anay-=1;
		}
	}
	return ret;
}
#else
//分析查找合法包
uint8_t X_Uart1_Analyze(uint8_t *recvbuf,X_Order_t *order)
{

	static uint16_t anay = 0;//缓冲区空闲位置
	uint8_t ret = 0;
  //	uint16_t head = 0xffff,end = 0xffff;//标记当前循环是否找到 包头位置 包尾位置 合法包
	uint16_t len = X_UART1_Get_NewBuf(recvbuf+anay);
	anay+=len;
	for(int i=0;i<anay;i++)
	{
		if(recvbuf[i]=='\r')
		{
			recvbuf[i] = 0;
			char tmp[10];
			uint8_t len = AT_GetArgAt((char*)recvbuf,',',0,tmp);
			int mt = AT_Str2Int(tmp);
			len = AT_GetArgAt((char*)recvbuf,',',1,tmp);
			int spd = AT_Str2Int(tmp);
			len = AT_GetArgAt((char*)recvbuf,',',2,tmp);
			double rou = AT_Str2Dob(tmp);
			int rou_int = rou*100;
			anay = 0;
			order->order = spd;
			order->len = mt;
			order->cont[0] = (rou_int>>24)&0xff;
			order->cont[1] = (rou_int>>16)&0xff;
			order->cont[2] = (rou_int>>8)&0xff;
			order->cont[3] = (rou_int)&0xff;
			ret = 1;
		}
	}
	
	return ret;
}

//分析查找合法包
uint8_t X_Uart1_Analyze1(uint8_t *recvbuf,float *order)
{

	static uint16_t anay = 0;//缓冲区空闲位置
	uint8_t ret = 0;
	//uint16_t head = 0xffff,end = 0xffff;//标记当前循环是否找到 包头位置 包尾位置 合法包
	uint16_t len = X_UART1_Get_NewBuf(recvbuf+anay);
	anay+=len;
	for(int i=0;i<anay;i++)
	{
		if(recvbuf[i]=='\r')
		{
			recvbuf[i] = 0;
			char tmp[10];
			uint8_t num = AT_ArgNUM((char *)recvbuf,',');
			for(int i=0;i<num;i++)
			{
				uint8_t len = AT_GetArgAt((char *)recvbuf,',',i,tmp);
				order[i] = AT_Str2Dob(tmp);
			}
			order[num] = 0;
			order[num+1] = 0;
			anay = 0;
			ret = 1;
		}
	}
	
	return ret;
}
#endif
//分析查找合法包
uint8_t X_Uart_Analyze_MDBUS(uint8_t *recvbuf,X_Modbus_Order_t *order)
{
	static uint16_t anay = 0;//缓冲区空闲位置
	uint8_t ret = 0;
	uint16_t head = 0,end = 0;//标记当前循环是否找到 包头位置 包尾位置 合法包
	uint16_t len = X_UART1_Get_NewBuf(recvbuf+anay);
	anay+=len;
	while((anay-head)>=8)
	{
		if(recvbuf[head] == Modbus_Slave_Addr) 
		{
			switch(recvbuf[head+1])
			{
				case 0x03:	//读多个寄存器
				{
					uint16_t crc = modbuscrc16(recvbuf+head,6);
					end = head+6;
					if(crc == ((recvbuf[end]<<8)|recvbuf[end+1]))
					{
						order->func = recvbuf[head+1];
						order->addr = recvbuf[head+2]*256+recvbuf[head+3];
						order->len = recvbuf[head+4]*256 + recvbuf[head+5];
						ret = 1;
						break;
					}
					else
					{
						head++;
						end = 0;
						continue;
					}
					//break;
				}
				case 0x06:	//写单个寄存器
				{
					uint16_t crc = modbuscrc16(recvbuf+head,6);
					end = head+6;
					if(crc == ((recvbuf[end]<<8)|recvbuf[end+1]))
					{
						order->func = recvbuf[head+1];
						order->addr = recvbuf[head+2]*256+recvbuf[head+3];
						order->len = 1;
						order->val[0] = recvbuf[head+4];
						order->val[1] = recvbuf[head+5];
						ret = 1;
						break;
					}
					else
					{
						head++;
						end = 0;
						continue;
					}

				}//break;
				case 0x10:	//写多个寄存器
				{
					static uint16_t delay = 0;//如果被拆包，延迟等待几次
					uint16_t num = recvbuf[head+6];//(recvbuf[head+4]*256+recvbuf[head+5])*2;//数据长度
					if((anay-head)>=(num+7))
					{
						uint16_t crc = modbuscrc16(recvbuf+head,num+7);
						end = head+7+num;
						if(crc == ((recvbuf[end]<<8)|recvbuf[end+1]))
						{
							order->func = recvbuf[head+1];
							order->addr = recvbuf[head+2]*256+recvbuf[head+3];
							order->len = recvbuf[head+4]*256 + recvbuf[head+5];
							for(int i=0;i<num;i++)
							{
								order->val[i] = recvbuf[head+7+i];
							}
							delay = 0;
							ret = 1;
							break;
						}
						else
						{
							head++; 
							end = 0;
							continue;
						}
					}
					else
					{
						if(++delay>3)
						{
							delay = 0;
							head++;
						}
						continue;//尝试等待几次看能不能接收到更多的数据
					}
				}//break;
				default:
					head++;
					end = 0;
				break;
			}
		}
		else
		{
			head++;
			end = 0;
		}
		if(ret == 1)
			break;
	}
	if(ret == 0)
	{
		end = head;
	}
	else 
	{
		end+=2;
	}
	if(end > 0)
	{
		for(int i=0;i<(anay-end);i++) //把包从当前缓冲中去掉。
		{
			recvbuf[i] = recvbuf[end+i];
		}
		anay = anay-end;
	}
	
	return ret;

}


/*DMA溢出中断回调函数*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		__HAL_UART_GET_FLAG(&huart1,UART_FLAG_ORE);
	}
//	 if(huart == &huart2)
//	{
//		__HAL_UART_GET_FLAG(&huart2,UART_FLAG_ORE);
//	}

}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	
	if(huart == &huart1)
	{
//		HAL_GPIO_WritePin(USART1_DE_GPIO_Port,USART1_DE_Pin,GPIO_PIN_RESET);   /* 485 DE */
	}
// if(huart == &huart2)
//	{
//		HAL_GPIO_WritePin(USART2_DE_GPIO_Port,USART2_DE_Pin,GPIO_PIN_RESET);
//		//HAL_UART_Receive_DMA(&huart2,XUART3_Buf,XUART3_Buf_Len);
//	}
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
