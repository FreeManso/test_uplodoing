
#ifndef __MODBUS_H__
#define __MODBUS_H__
//#include "main.h"
#include "user_def.h"





#define MODBUS_ADDR_MODNAME 		(XUSER_MODBUS_CFG_BASE + 0*W25XX_SECTOR_LEN)		//ģ������
#define MODBUS_ADDR_MODSN 			(XUSER_MODBUS_CFG_BASE + 1*W25XX_SECTOR_LEN)		//��Ʒϵ�к�
#define MODBUS_ADDR_MODREGI			(XUSER_MODBUS_CFG_BASE + 2*W25XX_SECTOR_LEN)		//��еע���
#define MODBUS_ADDR_SOFTWARE		(XUSER_MODBUS_CFG_BASE + 3*W25XX_SECTOR_LEN)		//����汾��
#define MODBUS_ADDR_HARDWARE		(XUSER_MODBUS_CFG_BASE + 4*W25XX_SECTOR_LEN)		//Ӳ���汾��
#define MODBUS_ADDR_PRDTDATA		(XUSER_MODBUS_CFG_BASE + 5*W25XX_SECTOR_LEN)		//��������
#define MODBUS_ADDR_CONTRACT		(XUSER_MODBUS_CFG_BASE + 6*W25XX_SECTOR_LEN)		//���ۺ�ͬ
#define MODBUS_ADDR_QUALITY			(XUSER_MODBUS_CFG_BASE + 7*W25XX_SECTOR_LEN)		//�ʼ���

#define MODBUS_ADDR_MT1			(XUSER_MODBUS_CFG_BASE + 8*W25XX_SECTOR_LEN)		//PST�������
#define MODBUS_ADDR_MT1SPEED		(XUSER_MODBUS_CFG_BASE + 9*W25XX_SECTOR_LEN)		//PST����ٶȵ�

#define MODBUS_ADDR_MT2			(XUSER_MODBUS_CFG_BASE +10*W25XX_SECTOR_LEN)		//Z�������
#define MODBUS_ADDR_MT2SPEED			(XUSER_MODBUS_CFG_BASE +11*W25XX_SECTOR_LEN)		//Z����ٶȵ�

#define MODBUS_ADDR_MT3			(XUSER_MODBUS_CFG_BASE +12*W25XX_SECTOR_LEN)		//ZJ�������
#define MODBUS_ADDR_MT3SPEED			(XUSER_MODBUS_CFG_BASE +13*W25XX_SECTOR_LEN)		//ZJ����ٶȵ�

#define MODBUS_ADDR_MT4			(XUSER_MODBUS_CFG_BASE +14*W25XX_SECTOR_LEN)		//ZR�������
#define MODBUS_ADDR_MT4SPEED			(XUSER_MODBUS_CFG_BASE +15*W25XX_SECTOR_LEN)		//ZR����ٶȵ�


#define MODBUS_ADDR_STDEYTIME			(XUSER_MODBUS_CFG_BASE +70*W25XX_SECTOR_LEN)		//״̬λ��λ��ʱʱ��


#define TEMP_COMP			(XUSER_MODBUS_CFG_BASE +80*W25XX_SECTOR_LEN)		/* �¶Ȳ��� */


#define STATUS_00_ORDERT	(0x00000001<<0)		//����ִ��״̬
#define STATUS_01_SELFTEST	(0x00000001<<1)		//�Լ����
#define STATUS_02_HAVETIP	(0x00000001<<2)		//����ǹͷ
#define STATUS_03_HAVELIQ	(0x00000001<<3)		//ǹ����Һ��
#define STATUS_04_TOUCHLV	(0x00000001<<4)		//����Һ��
#define STATUS_05_PSTMOVE	(0x00000001<<5)		//PST�������״̬
#define STATUS_06_ZMTMOVE	(0x00000001<<6)		//Z��������״̬
#define STATUS_07_CHECKMD	(0x00000001<<7)		//У��״̬

#define STATUS_08_ERRPRSS	(0x00000001<<8)		//ѹ������������
#define STATUS_09_ERRMTN	(0x00000001<<9)		//���δ��λ
#define STATUS_10_ERRPSTG	(0x00000001<<10)	//ȡ��ǹ����
#define STATUS_11_ERRKEYN	(0x00000001<<11)	//�ؼ�������ʧ
#define STATUS_12_ERRSUCK	(0x00000001<<12)	//����������г�
#define STATUS_13_ERRCEKN	(0x00000001<<13)	//У��ʧ��
#define STATUS_14_ERRSPDN	(0x00000001<<14)	//����δ�����ٶȵ�
#define STATUS_15_ERRADDN	(0x00000001<<15)	//��дδ�����ַ

#define STATUS_17_NOTOUCH	(0x00000001<<17)	//δ��⵽Һ��
#define STATUS_20_ABSORBNL	(0x00000001<<20)	//����

#define STATUS_21_ZJMOVE	(0x00000001<<5)		//ZJ��������״̬
#define STATUS_22_JAWMOVE	(0x00000001<<6)		//JAW����״̬

#define STATUS_23_TIPJAM	(0x00000001<<23)	//��������
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




void X_Set_Order_RunStart(int mode);   //���������ʱ��
void X_Set_Order_Runover(int mode);




void modbus_message_dispose(X_Modbus_Order_t *order);

void modbus_setstatus(uint32_t bit,X_BITSET_t set);


X_BITSET_t modbus_getstatus(uint32_t bit );

void X_CliSoft_ToFlash(uint32_t alllen);

uint8_t X_SaveSoft_FromCMP(uint16_t num,uint8_t *arg);
void X_SIGUPDATA_True(uint8_t *up);
/*��ʼ��*/
void TempStructInit(void);
/* ��ȡ�¶Ȳ������߲��� */
int32_t message_TempComp_read(X_Modbus_Order_t *order,uint32_t flash);


/* �����¶Ȳ������߲��� */
int32_t message_TempComp_write(X_Modbus_Order_t *order,uint32_t flash);

/*��ȡ����״̬*/
int32_t message_WorkMode(X_Modbus_Order_t *order,uint32_t flash);

/* ��ȡ������¶� */
int32_t message_TempData_read(X_Modbus_Order_t *order,uint32_t flash);

/* ��ȡ��һ�α�����¶� */
int32_t message_TemplastData_read(X_Modbus_Order_t *order,uint32_t flash);
/*  ���ö�ȡǰ���� */
int32_t message_TempLastData_write(X_Modbus_Order_t *order,uint32_t flash);
int32_t message_uid_read(X_Modbus_Order_t *order,uint32_t flash);
#endif /* __MODBUS_H__ */
