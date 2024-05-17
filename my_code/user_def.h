#ifndef __USER_DEF_H
#define __USER_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"


#define software_version_big 1
#define software_version_sml 5

#define hardware_version_big 1
#define hardware_version_sml 0


#define X_SET_GPIO_HIGH(X_IO,X_PIN) (X_IO)->BSRR = X_PIN
#define X_SET_GPIO_LOW(X_IO,X_PIN) (X_IO)->BSRR = (uint32_t)X_PIN << 16U
#define X_GPIO_IS_LOW(X_IO,X_PIN) (X_IO->IDR & X_PIN) == (uint32_t)GPIO_PIN_RESET
#define X_GPIO_IS_HIG(X_IO,X_PIN) (X_IO->IDR & X_PIN) != (uint32_t)GPIO_PIN_RESET
#define X_SET_GPIO_TOG(X_IO,X_PIN) (X_IO)->ODR ^= X_PIN


#define MD_DFT_BL 0


//����������λ�ã���������������飬����ʱ��ֻ��ȡBASE0���ݣ�
//��BASE0������֤����ʱ�򣬻��ȡBASE1����BASE0,
//���BASE1Ҳ��֤����ʱ��������޷�ִ�У�ֱ��������ȷ�Ĳ�����
#if 1

//����������flash
#define XUSER_DATA_TYPE 2

#define XUSER_DATA_ADDR_BASE0 (W25XX_MEMORY-W25XX_BLOCK_LEN) //���һ��64K
#define XUSER_DATA_ADDR_BASE1 (XUSER_DATA_ADDR_BASE0-W25XX_BLOCK_LEN)  //�����ڶ���64K
#define XUSER_MTARG_STEP W25XX_SECTOR_LEN  //ÿ������������ռ��4K ������16��������

#define XUSER_TEMP_CFG_BASE0 (W25XX_MEMORY-3*W25XX_BLOCK_LEN) //����������64K
#define XUSER_TEMP_CFG_BASE1 (W25XX_MEMORY-4*W25XX_BLOCK_LEN) //����������64K

#define XUSER_MECHINE_CFG_BASE0 (W25XX_MEMORY-5*W25XX_BLOCK_LEN) //����������64K
#define XUSER_MECHINE_CFG_BASE1 (W25XX_MEMORY-6*W25XX_BLOCK_LEN) //����������64K
#define XUSER_MECHINE_BASE_OFFSET 0   //Ӳ����׼ƫ��ֵ
#define XUSER_MECHINE_WH_OFFSET W25XX_SECTOR_LEN //�ۿ���Ϣƫ��ֵ

#define XUSER_INFO_CFG_BASE0 (W25XX_MEMORY-7*W25XX_BLOCK_LEN) //������7��64K
#define XUSER_INFO_CFG_BASE1 (W25XX_MEMORY-8*W25XX_BLOCK_LEN) //������8��64K


#define XUSER_PST_ADJ_BASE0 (W25XX_MEMORY-9*W25XX_BLOCK_LEN) //������9��10��128K
#define XUSER_PST_ADJ_BASE1 (W25XX_MEMORY-11*W25XX_BLOCK_LEN) //������11��12��128K


#define XUSER_FLOW_START_ADDR   0x100000//�������̿�ʼ�洢λ�� �ݶ���1M��ʼ��λ�ã�ǰ��Ԥ��1M
#define XUSER_FLOW_STORE_SPACE	0x10000 	//��������Ԥ���ռ� 64K ǰ��4K���ڴ洢������Ϣ ���Դ洢1920��ָ��
#define XUSER_FLOW_INFO_SPACE 0x1000	//������Ŀ��Ϣ�Ŀռ� 4�ֽ����� 252�ֽڵ����ƿռ� ʣ�µı���
#define XUSER_FLOW_MAX_NUM (14*1024*1024/XUSER_FLOW_STORE_SPACE) //����������� 14M�Ŀռ����洢���� ���223������
#define FLOW_STEP_MAXLEN 32 //����ָ��� Ŀǰ24�ֽ� Ԥ��8�ֽ���չ

#define XUSER_SOFT_BACKUP_ADDR (0x0+W25XX_BLOCK_LEN) //����������������ʼ��ַƫ��64K�ĵط� ���1M�ĵ�ַ
#define XUSER_SOFT_BAG_LEN (128)

#endif



#define XUSER_MODBUS_CFG_BASE 		(0xE00000) 	//��modbus������flash�����ʼ��ַ
#define XUSER_MODBUS_CFG_BACK		(W25XX_PAGE_LEN) 	//ÿ�����ݱ��ݵ�ַƫ�� 


#define  XUSER_TEMP_BASE   (0x100000)  //�¶����ݵ�ַ

#define XUART1_Buf_Len 512
#define XUART2_Buf_Len 512
#define XUART3_Buf_Len 512

#define XPRE_Buf_Len 64
//ϵͳģ��ö��
typedef enum 
{
	MD_SECT   = 0,		//���ô����
	MD_MOTOR,			//���ģ��
	MD_WARM,			//����ģ��
	MD_FAN,				//����ģ��
	MD_UV,				//�����ģ��
	MD_LOCK,			//�����ģ��
	MD_LIGH,			//����ģ��
	MD_CON,				//����ģ��
	MD_USB,				//USBģ��
	MD_CAN,				//CANģ��
	MD_FREE,			//һ�����̽����ͷ�
	MD_ALL
}X_MODE_t;
	
/**
  * @brief ������
  */
typedef enum 
{
	MT_DRV1 = 0,
	MT_DRV2 = 1,
	MT_NDRV3 = 2,
	MT_NDRV4 = 3,
	ALL_MT
}X_Motor_t;

/**
  * @brief ͨѶָ����������
  */
typedef enum 
{
	OD_NULL = 0x00,			//��ָ��
	OD_PST ,				//����pst����
	OD_ZMT,					//����z�ᶯ��
	OD_PICK,				//ȡ��ǹͷ
	OD_ONCE  ,				//��������
	OD_CYLIC ,				//ѭ������
	OD_DELAY ,				//��ʱ
	ALL_OD
}X_ORDER_t;

/**
  * @brief �׸� �׵�
  */
typedef enum 
{
	HOLE_BTM = 0,
	HOLE_TOP,
	HOLE_BASE
}X_Hole_Pos_t;

/**
  * @brief �����
  */
#define XUART_Order_Len (256)

typedef struct
{
	uint8_t order;
	uint8_t len;
	uint8_t cont[XUART_Order_Len];
}X_Order_t;

typedef union
{
	int32_t xi;
	int8_t xc[4];
}X_Int_Char;

typedef union
{
	int16_t xs;
	int8_t xc[2];
}X_Sot_Char;
/**
  * @brief ��PCͨ��ָ���ʽ��
  */
typedef struct
{
	uint32_t head;
	X_Order_t order;
	uint16_t crc;
	uint32_t end;
}X_PCBAG_t;

/**
  * @brief ���õĵ���ٶ� RPMģʽ
  */
__packed typedef struct
{
	uint16_t upstep;		//���ٲ��� ���ٲ���Ϊ0��ʱ���ʾ����
	uint16_t minrpm;		//����Ƶ�� ÿ����ת�� ʵ��ֵ = minrpm/10
	uint16_t maxrpm;  		//���Ƶ�� ÿ����ת�� ʵ��ֵ = maxrpm/10
}X_MTSPDRPM_t;


/**
  * @brief ������������ṹ��
  */
__packed typedef struct
{
	uint8_t use;	//0:��ʹ�� 1��ʹ��
	float posrou;		//������г�    ��λmm
	float negrou;		//������г�    ��λmm
	float zero;		//���ƫ�� ������ ����ֵ
	uint16_t maxspd;  	//���ת�� RPM
	uint16_t scale;		//���ϸ�� һȦ���� 200,400,800����
	uint8_t rstdir; 	//��λ���� 0��ת��1��ת
	uint8_t stopamp; 	//ֹͣ���� 1ȫ�� 2���� 1/N��
	uint16_t amp;		//�������� mA
	float hlcpitch;	//����  ��λmm
	X_MTSPDRPM_t defspd[21]; //10��ϵͳ�ٶ�
	int32_t valpos[10];	//10��λ�ñ���ֵ 
	char name[16];		//�������
}X_MTARG_t;


/**
  * @brief ���õ�������ṹ�� OD_SETMT
  */
__packed typedef struct
{
    uint8_t mt;   //���
    uint8_t rw;	//0:��ȡ 1������      0xff:��λ����
	X_MTARG_t arg; //����
}X_SETMT_t;

//�¶ȿ���pid 
__packed typedef struct
{
	uint8_t chn;   		//����ͨ��
	uint8_t rw; 		//0:��ȡ 1������
	uint8_t debug; 		//��������ģʽ     ��Ϊ0ʱÿ���ϱ�һ���¶�
	int32_t Proportion;	//??��������??Proportional??Const
	int32_t Integral;	//??���ֳ���??Integral??Const??
	int32_t Derivative;	//??΢�ֳ���??Derivative??Const????
	int16_t aimtemp;	// ����Ŀ���¶�
}X_SETTMP_t;

//�¶ȿ���



/**
  * @brief ��������ظ�ʽ OD_DWST
  */
__packed typedef struct
{
    uint8_t ser;    //����α�� 0-127
    uint8_t type;   //0;ͷ�� 1������ 2������
	uint16_t cur;  //��ǰ����
	uint16_t all;  //�ܰ���
	uint8_t data[128]; //����
}X_DWST_t;




typedef enum 
{
	WM_MD1   = 0,		//����ģ��1
    WM_MD2   = 1,		//����ģ��2
    WM_MD3   = 2,		//����ģ��3
    WM_MD4   = 3,		//����ģ��4
    WM_ALL
}X_WARM_t;



/**
  * @brief ����ٶȽṹ�壬����λ������
  */
__packed typedef struct
{
	uint16_t upstep;	//���ٲ��� ���ٲ���Ϊ0��ʱ���ʾ����
	uint32_t min;		//����Ƶ��
	uint32_t max;  		//���Ƶ��
	float fle;			//�Ӽ��ٱ仯�ʣ� ֵԽ�ӽ�0Խ�����ȼ��� �� Խ���ٶȱ仯Խ�죬����4-5
}X_MTSPD_t;




/**
  * @brief ����ٶȿ��ټ�����̲���
  */
__packed typedef struct
{
	X_MTSPD_t ini;  //�ٶȲ���
	uint32_t uprou;	//������ֹ�� (0,n)
	uint32_t csrou;	//������ֹ�� (n+1,m)
	uint32_t dwrou;	//������ֹ�� (m+1,rou)
	uint32_t step;	//��¼���߲���
	float fpre; 	//�����ϴ����ֵ
	float fexp;		//����ָ������ֵ ���ڿ��ټ���
	uint16_t arr;	//���ö�ʱ��arr��ֵ
	uint32_t fre;	//��ʱ��Ƶ��
	uint32_t fredif;  //����Ƶ�ʺ����Ƶ�ʵĲ�ֵ

}X_MTSPD_PROC_t;





//����˶�����ָ��ö��
typedef enum 
{
	MTCTR_RST_POS = 0,		//ִ�и�λ    �������ֹͣ
	MTCTR_SET_ORG = 1,		//����ǰλ������Ϊ����ֵ �����������λ�ñ�ΪĿ��ֵ
	MTCTR_ABS_POS = 2,		//�õ��ʹ�þ���λ�÷�ʽ����
	MTCTR_REL_POS = 3,		//���λ�� 
	MTCTR_DEF_POS = 4,		//�õ�����е�Ԥ��λ�� 
	MTCTR_WAT_STP = 5,		//�ȴ�����˶���ֹͣ
	MTCTR_WAT_ITR ,			//�ȴ�����˶����뿪���
	MTCTR_WAT_DEL ,		//��ʱ�ȴ�һ��ʱ�� ������޹� ���Ǵ������ȴ�ʱ��
	MTCTR_RUN_ZERO,		//���е����ƫ��
	MTCTR_WAT_PIO ,		//�õ������ֱ��IO���ź�����
	MTCTR_WAT_UAT ,		//�õ������ֱ���յ�ĳ��������Ϣ
	MTCTR_RUN_CIR,		//����תȦģʽ
	MTCTR_LOW_STP,		//�������ͣ��
	MTCTR_READ = 0xfe,		//��ȡ���״̬
	MTCTR_END = 0xff  //��������һ�����̽������������κε��
}X_MTCTR_t;



/**
  * @brief �����������
  */
typedef struct
{
	GPIO_TypeDef *dir_gp;	//�����������
	uint16_t	dir_io;
	
	GPIO_TypeDef *pwm_gp;	//��������
	uint16_t	pwm_io;
	
	GPIO_TypeDef *int_gp;	//��λ��������
	uint16_t	int_io;
	
	GPIO_TypeDef *en_gp;	//ʹ������
	uint16_t	en_io;

	GPIO_TypeDef *half_gp;	//������������
	uint16_t	half_io;
	
	GPIO_TypeDef *limit_gp;	//���Ƶ�������
	uint16_t	limit_io;
	
}X_Motor_IO_t;


/**
  * @brief ����˶����ƽṹ��
  */
typedef struct
{
	uint8_t use;	//�Ƿ��г�ʼ���õ�� 0:û 1:��
	uint8_t run;	//����Ƿ����� 0:ֹͣ 1:����
	uint8_t rst;	//��0��ʾִ�е����λ
	uint8_t dir;	//Ŀǰ����н����� 0��ԭ�㷽�� 1��Զ��ԭ�㷽��
	int32_t cur;	//�����ǰλ�� ������  
	int32_t rou;	//���г� 
	uint8_t itr;	//��翪��״̬ 0���뿪���� 1��������״̬ 
	uint8_t cir;	//תȦģʽ תȦģʽ�� �뿪���·�̻��Զ�����
	X_MTARG_t *arg; 	//�����ĵ����������
	X_MTSPD_t spd[23];	//10���ٶȲ���
	int32_t valpos[10];	//10�����ֵ
	X_MTSPD_PROC_t proc; //������̲��� ÿ������ǰ����ã������жϹ����еļ���ʱ��
	TIM_HandleTypeDef *time;//������ʱ�� 
	uint32_t channel;//������ʱ��ͨ��
	X_Motor_IO_t pio; //��������
}X_Motor_Run_t;





/**
* @brief ��mode��X_MODE_t  = MD_MOTOR arg��������
*/
__packed typedef struct
{
	uint8_t mt;     //������ X_Motor_t
	uint8_t ctr;    //�������� X_MTCTR_t
	uint8_t spd;  	//�ٶȱ������
	float pos;    //�˶���������λ�û�λ�ñ�Ż���ʱʱ���ǰλ��
}X_MT_ARG_t;




/**
* @brief ʹ�����䴫��ʱ��ȷ�����ݵȳ�
*/
__packed typedef struct
{
	uint8_t order;	    //��Ҫ���Ƶ�ģ��
	uint8_t arg[20];    //�����Ĳ���  ���������涨��
}X_SYS_CTR_t;








/**
  * @brief modbus�����
  */

__packed typedef struct
{
	uint8_t func;	//���ܺ���
	uint16_t addr;	//��ַ
	uint16_t len;		//�ֽ���
	uint8_t val[XUART3_Buf_Len];	//����
}X_Modbus_Order_t;

/**
  * @brief HF�������ָ�����
  */
__packed typedef struct
{
	int16_t step;	//������
	int8_t prog;	//������
	int8_t crc;	//CRC��֤
	float arg[5];	//ÿ���������5������
}X_FlowStep_t;






/**
  * @brief ���õĵ���ٶ� RPMģʽ
  */
__packed typedef struct
{
	uint16_t minrpm;		//����Ƶ�� ÿ����ת�� ʵ��ֵ = minrpm
	uint16_t maxrpm;  		//���Ƶ�� ÿ����ת�� ʵ��ֵ = maxrpm
	uint16_t upstep;		//���ٲ��� ���ٲ���Ϊ0��ʱ���ʾ����
}XMD_RPMSPEED_t;

/**
  * @brief ���õĵ���ٶ�     Ƶ��ģʽ
  */
__packed typedef struct
{
	uint32_t minfre;		//����Ƶ�� ÿ����ת�� ʵ��ֵ = minrpm
	uint32_t maxfre;  		//���Ƶ�� ÿ����ת�� ʵ��ֵ = maxrpm
	uint16_t upstep;		//���ٲ��� ���ٲ���Ϊ0��ʱ���ʾ����
}XMD_SPEED_t;


/**
  * @brief ������������ṹ��
  */
__packed typedef struct
{
	float hlcpitch;	//���� ʵ��ֵ = hlcpitch/100 ��λmm
	uint16_t scale;		//���ϸ�� һȦ���� 200,400,800����
	uint16_t rstdir; 	//��λ���� 0��ת��1��ת
	float zero;		//���ƫ�� mm
	uint16_t amp;		//�������� mA
	float posrou;	//������г� ʵ��ֵ = posrou/100 ��λmm
	float negrou;	//������г� ʵ��ֵ = negrou/100 ��λmm
	uint16_t maxspd;  	//���ת�� RPM
}XMD_MTARG_t;

/**
  * @brief ������������ṹ��
  */
__packed typedef struct
{
	XMD_MTARG_t arg;
	XMD_SPEED_t spd[21]; //Ԥ�� ���һ��������ʱ�ٶ�
}XMD_MT_t;


/**
  * @brief ���̶���
  */
__packed typedef struct
{
	float volume;	//����
	float accuracy;	//����
	float moveul;	//ÿul�ƾ�
	float pststart;	//������λ��
}XMD_VL_t;

/**
  * @brief ��Һλ�ò���
  */
__packed typedef struct
{
	float hole;	//�ھ� mm
	float btm;	//�ײ�λ��
	float top;	//����λ��
	float base;	//�˸�
	float volm;	//ǹͷ��� ul
}XMD_HOLE_t;

/**
  * @brief ȡ��ǹ����
  */
__packed typedef struct
{
	float pickhigh;	//ȡǹ�߶�
	float lap;		//��ϸ߶�
	float pstvol;		//ǹͷ���
	float outhigh;	//��ǹ�߶�
	float pstpos;	//��ǹλ��
	uint8_t zspd;	//ȡǹ�ٶ�
	uint8_t pstspd;	//��ǹ�ٶ�
	float base;		//��׼��ǹ�˸�λ��ĸ߶�
	float pstlen;	//ǹͷ����
}XMD_PICK_t;


/**
  * @brief �������²���
  */
__packed typedef struct
{
	float vol;	//������� ul
	int16_t mode;	//����ģʽ
	float depth;	//������� 0.01mm
	int8_t pstspd;	//�����ٶ�
	int8_t zspd;	//Z�����ٶ�
	int32_t time;	//������ʱ 0.01s
	float ohigh;	//��λ��߶� 0.01mm ��۵�
	float exvol;	//��λ�������
	int16_t area;	//����
}XMD_ONCEXT_t;

/**
  * @brief ѭ�����²���
  */
__packed typedef struct
{
	float vol;	//������� ul
	uint16_t num;	//���´���
	int8_t zspd;	//Z�����ٶ�
	float xhigh;	//����
	float thigh;	//�¸�
	int8_t xspd;	//����
	int8_t tspd;	//����
	int32_t xtime;	//������ʱ 0.01s
	int32_t ttime;	//������ʱ 0.01s
	float ohigh;	//��λ��߶� 0.01mm ��۵�
	int16_t area;	//����
}XMD_LOOPXT_t;

/**
  * @brief Һ�������
  */
__packed typedef struct
{
	
	int16_t zspd;	//Z�����ٶ�
	int16_t stop;	//ֹͣλ��
	int16_t area;	//����
}XMD_DECTXT_t;


/**
  * @brief PST�궨����
  */
__packed typedef struct
{
	float a;	//
	float b;	//
	float c;	//
	float d;	//
	float e;	//
	float f;	//
}XMD_PSTCAL_t;

//
typedef enum 
{
	MODBUS_BIT_CLI = 0,
	MODBUS_BIT_SET	
}X_BITSET_t;
	



#endif
