
#ifndef __MODBUS_H__
#define __MODBUS_H__
//#include "main.h"
#include "user_def.h"





#define MODBUS_ADDR_MODNAME 		(XUSER_MODBUS_CFG_BASE + 0*W25XX_SECTOR_LEN)		//模块名称
#define MODBUS_ADDR_MODSN 			(XUSER_MODBUS_CFG_BASE + 1*W25XX_SECTOR_LEN)		//产品系列号
#define MODBUS_ADDR_MODREGI			(XUSER_MODBUS_CFG_BASE + 2*W25XX_SECTOR_LEN)		//器械注册号
#define MODBUS_ADDR_SOFTWARE		(XUSER_MODBUS_CFG_BASE + 3*W25XX_SECTOR_LEN)		//软件版本号
#define MODBUS_ADDR_HARDWARE		(XUSER_MODBUS_CFG_BASE + 4*W25XX_SECTOR_LEN)		//硬件版本号
#define MODBUS_ADDR_PRDTDATA		(XUSER_MODBUS_CFG_BASE + 5*W25XX_SECTOR_LEN)		//出厂日期
#define MODBUS_ADDR_CONTRACT		(XUSER_MODBUS_CFG_BASE + 6*W25XX_SECTOR_LEN)		//销售合同
#define MODBUS_ADDR_QUALITY			(XUSER_MODBUS_CFG_BASE + 7*W25XX_SECTOR_LEN)		//质检编号

#define MODBUS_ADDR_MT1			(XUSER_MODBUS_CFG_BASE + 8*W25XX_SECTOR_LEN)		//PST电机参数
#define MODBUS_ADDR_MT1SPEED		(XUSER_MODBUS_CFG_BASE + 9*W25XX_SECTOR_LEN)		//PST电机速度档

#define MODBUS_ADDR_MT2			(XUSER_MODBUS_CFG_BASE +10*W25XX_SECTOR_LEN)		//Z电机参数
#define MODBUS_ADDR_MT2SPEED			(XUSER_MODBUS_CFG_BASE +11*W25XX_SECTOR_LEN)		//Z电机速度档

#define MODBUS_ADDR_MT3			(XUSER_MODBUS_CFG_BASE +12*W25XX_SECTOR_LEN)		//ZJ电机参数
#define MODBUS_ADDR_MT3SPEED			(XUSER_MODBUS_CFG_BASE +13*W25XX_SECTOR_LEN)		//ZJ电机速度档

#define MODBUS_ADDR_MT4			(XUSER_MODBUS_CFG_BASE +14*W25XX_SECTOR_LEN)		//ZR电机参数
#define MODBUS_ADDR_MT4SPEED			(XUSER_MODBUS_CFG_BASE +15*W25XX_SECTOR_LEN)		//ZR电机速度档


#define MODBUS_ADDR_STDEYTIME			(XUSER_MODBUS_CFG_BASE +70*W25XX_SECTOR_LEN)		//状态位置位延时时间


#define TEMP_COMP			(XUSER_MODBUS_CFG_BASE +80*W25XX_SECTOR_LEN)		/* 温度补偿 */


#define STATUS_00_ORDERT	(0x00000001<<0)		//命令执行状态
#define STATUS_01_SELFTEST	(0x00000001<<1)		//自检完成
#define STATUS_02_HAVETIP	(0x00000001<<2)		//悬挂枪头
#define STATUS_03_HAVELIQ	(0x00000001<<3)		//枪内有液体
#define STATUS_04_TOUCHLV	(0x00000001<<4)		//触碰液面
#define STATUS_05_PSTMOVE	(0x00000001<<5)		//PST电机动作状态
#define STATUS_06_ZMTMOVE	(0x00000001<<6)		//Z轴电机动作状态
#define STATUS_07_CHECKMD	(0x00000001<<7)		//校验状态

#define STATUS_08_ERRPRSS	(0x00000001<<8)		//压力传感器故障
#define STATUS_09_ERRMTN	(0x00000001<<9)		//电机未复位
#define STATUS_10_ERRPSTG	(0x00000001<<10)	//取退枪故障
#define STATUS_11_ERRKEYN	(0x00000001<<11)	//关键参数丢失
#define STATUS_12_ERRSUCK	(0x00000001<<12)	//吸吐体积超行程
#define STATUS_13_ERRCEKN	(0x00000001<<13)	//校验失败
#define STATUS_14_ERRSPDN	(0x00000001<<14)	//调用未定义速度档
#define STATUS_15_ERRADDN	(0x00000001<<15)	//读写未定义地址

#define STATUS_17_NOTOUCH	(0x00000001<<17)	//未检测到液面
#define STATUS_20_ABSORBNL	(0x00000001<<20)	//吸空

#define STATUS_21_ZJMOVE	(0x00000001<<5)		//ZJ轴电机动作状态
#define STATUS_22_JAWMOVE	(0x00000001<<6)		//JAW动作状态

#define STATUS_23_TIPJAM	(0x00000001<<23)	//吸到异物
/**
  * @brief 
  */
typedef  struct
{
	uint16_t B0:8;
	uint16_t B1:8;
}B16_t;

/**
  * @brief 
  */
typedef  struct
{
	uint32_t B0:8;
	uint32_t B1:8;
	uint32_t B2:8;
	uint32_t B3:8;
}B32_t;

/**
  * @brief 
  */
typedef union 
{
	uint16_t U;
	B16_t T;
}U16_t;




void modbus_init_motor(void);
void modbus_init_volume(void);
void modbus_init_pressure(void);
void modbus_init_adjpos(void);
void modbus_init_holearg(void);
void modbus_init_pickoutarg(void);
void modbus_init_stdeytime(void);
void modbus_init(void);
int32_t save_data_toflash(uint32_t addr,uint8_t *s_data, uint16_t length);
int32_t read_data_toflash(uint32_t addr,uint8_t *s_data, uint16_t length);




void X_Set_Order_RunStart(int mode);   //启动软件定时器
void X_Set_Order_Runover(int mode);




void modbus_message_dispose(X_Modbus_Order_t *order);

void modbus_setstatus(uint32_t bit,X_BITSET_t set);


X_BITSET_t modbus_getstatus(uint32_t bit );

void X_CliSoft_ToFlash(uint32_t alllen);

uint8_t X_SaveSoft_FromCMP(uint16_t num,uint8_t *arg);
void X_SIGUPDATA_True(uint8_t *up);
/*初始化*/
void TempStructInit(void);
/* 读取温度补偿曲线参数 */
int32_t message_TempComp_read(X_Modbus_Order_t *order,uint32_t flash);


/* 设置温度补偿曲线参数 */
int32_t message_TempComp_write(X_Modbus_Order_t *order,uint32_t flash);

/*读取工作状态*/
int32_t message_WorkMode(X_Modbus_Order_t *order,uint32_t flash);

/* 读取保存的温度 */
int32_t message_TempData_read(X_Modbus_Order_t *order,uint32_t flash);

/* 读取上一次保存的温度 */
int32_t message_TemplastData_read(X_Modbus_Order_t *order,uint32_t flash);
/*  设置读取前几次 */
int32_t message_TempLastData_write(X_Modbus_Order_t *order,uint32_t flash);
int32_t message_uid_read(X_Modbus_Order_t *order,uint32_t flash);
#endif /* __MODBUS_H__ */
