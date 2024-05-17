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


//保存电机参数位置，放置在最后两个块，启动时候只读取BASE0数据，
//当BASE0数据验证错误时候，会读取BASE1覆盖BASE0,
//如果BASE1也验证出错时候，则程序无法执行，直到设置正确的参数。
#if 1

//保存在外置flash
#define XUSER_DATA_TYPE 2

#define XUSER_DATA_ADDR_BASE0 (W25XX_MEMORY-W25XX_BLOCK_LEN) //最后一组64K
#define XUSER_DATA_ADDR_BASE1 (XUSER_DATA_ADDR_BASE0-W25XX_BLOCK_LEN)  //倒数第二组64K
#define XUSER_MTARG_STEP W25XX_SECTOR_LEN  //每组电机参数保留占用4K 共保存16组电机参数

#define XUSER_TEMP_CFG_BASE0 (W25XX_MEMORY-3*W25XX_BLOCK_LEN) //倒数第三组64K
#define XUSER_TEMP_CFG_BASE1 (W25XX_MEMORY-4*W25XX_BLOCK_LEN) //倒数第四组64K

#define XUSER_MECHINE_CFG_BASE0 (W25XX_MEMORY-5*W25XX_BLOCK_LEN) //倒数第五组64K
#define XUSER_MECHINE_CFG_BASE1 (W25XX_MEMORY-6*W25XX_BLOCK_LEN) //倒数第六组64K
#define XUSER_MECHINE_BASE_OFFSET 0   //硬件基准偏移值
#define XUSER_MECHINE_WH_OFFSET W25XX_SECTOR_LEN //槽孔信息偏移值

#define XUSER_INFO_CFG_BASE0 (W25XX_MEMORY-7*W25XX_BLOCK_LEN) //倒数第7组64K
#define XUSER_INFO_CFG_BASE1 (W25XX_MEMORY-8*W25XX_BLOCK_LEN) //倒数第8组64K


#define XUSER_PST_ADJ_BASE0 (W25XX_MEMORY-9*W25XX_BLOCK_LEN) //倒数第9和10组128K
#define XUSER_PST_ADJ_BASE1 (W25XX_MEMORY-11*W25XX_BLOCK_LEN) //倒数第11和12组128K


#define XUSER_FLOW_START_ADDR   0x100000//所有流程开始存储位置 暂定在1M开始的位置，前面预留1M
#define XUSER_FLOW_STORE_SPACE	0x10000 	//单个流程预留空间 64K 前面4K用于存储流程信息 可以存储1920条指令
#define XUSER_FLOW_INFO_SPACE 0x1000	//保存项目信息的空间 4字节索引 252字节的名称空间 剩下的保留
#define XUSER_FLOW_MAX_NUM (14*1024*1024/XUSER_FLOW_STORE_SPACE) //最大流程数量 14M的空间来存储流程 差不多223套流程
#define FLOW_STEP_MAXLEN 32 //单条指令长度 目前24字节 预留8字节扩展

#define XUSER_SOFT_BACKUP_ADDR (0x0+W25XX_BLOCK_LEN) //软件升级包存放在起始地址偏移64K的地方 最大到1M的地址
#define XUSER_SOFT_BAG_LEN (128)

#endif



#define XUSER_MODBUS_CFG_BASE 		(0xE00000) 	//将modbus保存在flash这个开始地址
#define XUSER_MODBUS_CFG_BACK		(W25XX_PAGE_LEN) 	//每个内容备份地址偏移 


#define  XUSER_TEMP_BASE   (0x100000)  //温度数据地址

#define XUART1_Buf_Len 512
#define XUART2_Buf_Len 512
#define XUART3_Buf_Len 512

#define XPRE_Buf_Len 64
//系统模块枚举
typedef enum 
{
	MD_SECT   = 0,		//内置代码段
	MD_MOTOR,			//电机模块
	MD_WARM,			//加热模块
	MD_FAN,				//风扇模块
	MD_UV,				//紫外灯模块
	MD_LOCK,			//电磁锁模块
	MD_LIGH,			//照明模块
	MD_CON,				//串口模块
	MD_USB,				//USB模块
	MD_CAN,				//CAN模块
	MD_FREE,			//一组流程结束释放
	MD_ALL
}X_MODE_t;
	
/**
  * @brief 电机编号
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
  * @brief 通讯指令命令类型
  */
typedef enum 
{
	OD_NULL = 0x00,			//空指令
	OD_PST ,				//控制pst动作
	OD_ZMT,					//控制z轴动作
	OD_PICK,				//取退枪头
	OD_ONCE  ,				//单次吸吐
	OD_CYLIC ,				//循环吸吐
	OD_DELAY ,				//延时
	ALL_OD
}X_ORDER_t;

/**
  * @brief 孔高 孔底
  */
typedef enum 
{
	HOLE_BTM = 0,
	HOLE_TOP,
	HOLE_BASE
}X_Hole_Pos_t;

/**
  * @brief 命令包
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
  * @brief 与PC通信指令格式。
  */
typedef struct
{
	uint32_t head;
	X_Order_t order;
	uint16_t crc;
	uint32_t end;
}X_PCBAG_t;

/**
  * @brief 内置的电机速度 RPM模式
  */
__packed typedef struct
{
	uint16_t upstep;		//加速步数 加速步数为0的时候表示匀速
	uint16_t minrpm;		//启动频率 每分钟转速 实际值 = minrpm/10
	uint16_t maxrpm;  		//最大频率 每分钟转速 实际值 = maxrpm/10
}X_MTSPDRPM_t;


/**
  * @brief 电机基本参数结构体
  */
__packed typedef struct
{
	uint8_t use;	//0:不使用 1：使用
	float posrou;		//正最大行程    单位mm
	float negrou;		//负最大行程    单位mm
	float zero;		//零点偏移 有正负 步数值
	uint16_t maxspd;  	//最大转速 RPM
	uint16_t scale;		//电机细分 一圈步数 200,400,800……
	uint8_t rstdir; 	//复位方向 0正转，1反转
	uint8_t stopamp; 	//停止电流 1全流 2半流 1/N流
	uint16_t amp;		//驱动电流 mA
	float hlcpitch;	//导程  单位mm
	X_MTSPDRPM_t defspd[21]; //10档系统速度
	int32_t valpos[10];	//10组位置变量值 
	char name[16];		//电机名称
}X_MTARG_t;


/**
  * @brief 设置电机参数结构体 OD_SETMT
  */
__packed typedef struct
{
    uint8_t mt;   //电机
    uint8_t rw;	//0:读取 1：设置      0xff:复位测试
	X_MTARG_t arg; //参数
}X_SETMT_t;

//温度控制pid 
__packed typedef struct
{
	uint8_t chn;   		//加热通道
	uint8_t rw; 		//0:读取 1：设置
	uint8_t debug; 		//启动调试模式     不为0时每秒上报一次温度
	int32_t Proportion;	//??比例常数??Proportional??Const
	int32_t Integral;	//??积分常数??Integral??Const??
	int32_t Derivative;	//??微分常数??Derivative??Const????
	int16_t aimtemp;	// 设置目标温度
}X_SETTMP_t;

//温度控制



/**
  * @brief 程序段下载格式 OD_DWST
  */
__packed typedef struct
{
    uint8_t ser;    //代码段编号 0-127
    uint8_t type;   //0;头部 1：变量 2：代码
	uint16_t cur;  //当前包号
	uint16_t all;  //总包号
	uint8_t data[128]; //内容
}X_DWST_t;




typedef enum 
{
	WM_MD1   = 0,		//加热模块1
    WM_MD2   = 1,		//加热模块2
    WM_MD3   = 2,		//加热模块3
    WM_MD4   = 3,		//加热模块4
    WM_ALL
}X_WARM_t;



/**
  * @brief 电机速度结构体，由上位机设置
  */
__packed typedef struct
{
	uint16_t upstep;	//加速步数 加速步数为0的时候表示匀速
	uint32_t min;		//启动频率
	uint32_t max;  		//最大频率
	float fle;			//加加速变化率， 值越接近0越趋近匀加速 ， 越大速度变化越快，建议4-5
}X_MTSPD_t;




/**
  * @brief 电机速度快速计算过程参数
  */
__packed typedef struct
{
	X_MTSPD_t ini;  //速度参数
	uint32_t uprou;	//加速终止步 (0,n)
	uint32_t csrou;	//匀速终止步 (n+1,m)
	uint32_t dwrou;	//减速终止步 (m+1,rou)
	uint32_t step;	//记录已走步数
	float fpre; 	//保存上次输出值
	float fexp;		//保存指数计算值 用于快速计算
	uint16_t arr;	//设置定时器arr的值
	uint32_t fre;	//定时器频率
	uint32_t fredif;  //启动频率和最大频率的差值

}X_MTSPD_PROC_t;





//电机运动控制指令枚举
typedef enum 
{
	MTCTR_RST_POS = 0,		//执行复位    遇到光电停止
	MTCTR_SET_ORG = 1,		//将当前位置设置为坐标值 电机不动作，位置变为目标值
	MTCTR_ABS_POS = 2,		//让电机使用绝对位置方式运行
	MTCTR_REL_POS = 3,		//相对位置 
	MTCTR_DEF_POS = 4,		//让电机运行到预设位置 
	MTCTR_WAT_STP = 5,		//等待电机运动到停止
	MTCTR_WAT_ITR ,			//等待电机运动到离开光电
	MTCTR_WAT_DEL ,		//延时等待一段时间 跟电机无关 就是纯粹插入等待时间
	MTCTR_RUN_ZERO,		//运行到零点偏移
	MTCTR_WAT_PIO ,		//让电机运行直到IO口信号跳变
	MTCTR_WAT_UAT ,		//让电机运行直到收到某个串口信息
	MTCTR_RUN_CIR,		//持续转圈模式
	MTCTR_LOW_STP,		//电机减速停机
	MTCTR_READ = 0xfe,		//读取电机状态
	MTCTR_END = 0xff  //用于宣告一个流程结束，不控制任何电机
}X_MTCTR_t;



/**
  * @brief 电机控制引脚
  */
typedef struct
{
	GPIO_TypeDef *dir_gp;	//方向控制引脚
	uint16_t	dir_io;
	
	GPIO_TypeDef *pwm_gp;	//脉冲引脚
	uint16_t	pwm_io;
	
	GPIO_TypeDef *int_gp;	//复位点检测引脚
	uint16_t	int_io;
	
	GPIO_TypeDef *en_gp;	//使能引脚
	uint16_t	en_io;

	GPIO_TypeDef *half_gp;	//半流控制引脚
	uint16_t	half_io;
	
	GPIO_TypeDef *limit_gp;	//限制点检测引脚
	uint16_t	limit_io;
	
}X_Motor_IO_t;


/**
  * @brief 电机运动控制结构体
  */
typedef struct
{
	uint8_t use;	//是否有初始化该电机 0:没 1:有
	uint8_t run;	//电机是否运行 0:停止 1:运行
	uint8_t rst;	//非0表示执行电机复位
	uint8_t dir;	//目前电机行进方向 0：原点方向 1：远离原点方向
	int32_t cur;	//电机当前位置 有正负  
	int32_t rou;	//总行程 
	uint8_t itr;	//光电开关状态 0：离开光电后 1：进入光电状态 
	uint8_t cir;	//转圈模式 转圈模式下 离开光电路程会自动归零
	X_MTARG_t *arg; 	//关联的电机基本参数
	X_MTSPD_t spd[23];	//10组速度参数
	int32_t valpos[10];	//10组变量值
	X_MTSPD_PROC_t proc; //计算过程参数 每次命令前计算好，减少中断过程中的计算时间
	TIM_HandleTypeDef *time;//关联定时器 
	uint32_t channel;//关联定时器通道
	X_Motor_IO_t pio; //关联引脚
}X_Motor_Run_t;





/**
* @brief 当mode：X_MODE_t  = MD_MOTOR arg参数定义
*/
__packed typedef struct
{
	uint8_t mt;     //电机编号 X_Motor_t
	uint8_t ctr;    //控制命令 X_MTCTR_t
	uint8_t spd;  	//速度变量编号
	float pos;    //运动距离或绝对位置或位置编号或延时时间或当前位置
}X_MT_ARG_t;




/**
* @brief 使用邮箱传递时候确保数据等长
*/
__packed typedef struct
{
	uint8_t order;	    //需要控制的模块
	uint8_t arg[20];    //附带的参数  参数由上面定义
}X_SYS_CTR_t;








/**
  * @brief modbus命令包
  */

__packed typedef struct
{
	uint8_t func;	//功能函数
	uint16_t addr;	//地址
	uint16_t len;		//字节数
	uint8_t val[XUART3_Buf_Len];	//数据
}X_Modbus_Order_t;

/**
  * @brief HF程序控制指令参数
  */
__packed typedef struct
{
	int16_t step;	//程序步骤
	int8_t prog;	//程序名
	int8_t crc;	//CRC验证
	float arg[5];	//每个步骤最多5个参数
}X_FlowStep_t;






/**
  * @brief 内置的电机速度 RPM模式
  */
__packed typedef struct
{
	uint16_t minrpm;		//启动频率 每分钟转速 实际值 = minrpm
	uint16_t maxrpm;  		//最大频率 每分钟转速 实际值 = maxrpm
	uint16_t upstep;		//加速步数 加速步数为0的时候表示匀速
}XMD_RPMSPEED_t;

/**
  * @brief 内置的电机速度     频率模式
  */
__packed typedef struct
{
	uint32_t minfre;		//启动频率 每分钟转速 实际值 = minrpm
	uint32_t maxfre;  		//最大频率 每分钟转速 实际值 = maxrpm
	uint16_t upstep;		//加速步数 加速步数为0的时候表示匀速
}XMD_SPEED_t;


/**
  * @brief 电机基本参数结构体
  */
__packed typedef struct
{
	float hlcpitch;	//导程 实际值 = hlcpitch/100 单位mm
	uint16_t scale;		//电机细分 一圈步数 200,400,800……
	uint16_t rstdir; 	//复位方向 0正转，1反转
	float zero;		//零点偏移 mm
	uint16_t amp;		//驱动电流 mA
	float posrou;	//正最大行程 实际值 = posrou/100 单位mm
	float negrou;	//负最大行程 实际值 = negrou/100 单位mm
	uint16_t maxspd;  	//最大转速 RPM
}XMD_MTARG_t;

/**
  * @brief 电机基本参数结构体
  */
__packed typedef struct
{
	XMD_MTARG_t arg;
	XMD_SPEED_t spd[21]; //预留 最后一个用于临时速度
}XMD_MT_t;


/**
  * @brief 量程定义
  */
__packed typedef struct
{
	float volume;	//容量
	float accuracy;	//精度
	float moveul;	//每ul移距
	float pststart;	//起吸点位置
}XMD_VL_t;

/**
  * @brief 吸液位置参数
  */
__packed typedef struct
{
	float hole;	//内径 mm
	float btm;	//底部位置
	float top;	//顶部位置
	float base;	//端高
	float volm;	//枪头体积 ul
}XMD_HOLE_t;

/**
  * @brief 取退枪参数
  */
__packed typedef struct
{
	float pickhigh;	//取枪高度
	float lap;		//配合高度
	float pstvol;		//枪头体积
	float outhigh;	//退枪高度
	float pstpos;	//退枪位置
	uint8_t zspd;	//取枪速度
	uint8_t pstspd;	//退枪速度
	float base;		//基准与枪端复位后的高度
	float pstlen;	//枪头长度
}XMD_PICK_t;


/**
  * @brief 单次吸吐参数
  */
__packed typedef struct
{
	float vol;	//吸吐体积 ul
	int16_t mode;	//吸吐模式
	float depth;	//吸吐深度 0.01mm
	int8_t pstspd;	//吸吐速度
	int8_t zspd;	//Z上下速度
	int32_t time;	//吸吐延时 0.01s
	float ohigh;	//出位后高度 0.01mm 离槽底
	float exvol;	//出位后过吸量
	int16_t area;	//保留
}XMD_ONCEXT_t;

/**
  * @brief 循环吸吐参数
  */
__packed typedef struct
{
	float vol;	//吸吐体积 ul
	uint16_t num;	//吸吐次数
	int8_t zspd;	//Z上下速度
	float xhigh;	//吸高
	float thigh;	//吐高
	int8_t xspd;	//吸速
	int8_t tspd;	//吐速
	int32_t xtime;	//吸吐延时 0.01s
	int32_t ttime;	//吸吐延时 0.01s
	float ohigh;	//出位后高度 0.01mm 离槽底
	int16_t area;	//保留
}XMD_LOOPXT_t;

/**
  * @brief 液面检测参数
  */
__packed typedef struct
{
	
	int16_t zspd;	//Z上下速度
	int16_t stop;	//停止位置
	int16_t area;	//区域
}XMD_DECTXT_t;


/**
  * @brief PST标定参数
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
