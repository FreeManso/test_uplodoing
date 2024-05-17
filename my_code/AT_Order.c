#include "stdio.h"
#include "string.h"
#include "AT_Order.h"
/*判定是否是需要的命令格式*/
unsigned char AT_IsOrder(char* head,char* end,char* order)
{
	if((strstr(order,head)!= NULL) && (strstr(order,end)!= NULL))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*判定是否存在当前指令*/
unsigned char AT_IncOrder(char* ins,char* order)
{
	if(strstr(order,ins)!= NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*获取当前命令文本的指令*/
unsigned char AT_GetIns(char* order,char head,char end,char* ins)
{
	int i=0;
	int len = strlen(order);
	int bcpy = 0;
	for(i=0;i<len;i++)
	{		
		if((bcpy == 1)&&(order[i] == end))
			break;
		if(bcpy) *ins++ = order[i];
		if((bcpy == 0)&&(order[i] == head))
			bcpy = 1;
	}
	if((bcpy == 1) && (i<len))
	{
		return 1;
	}
	else
		return 0;
}
/*获取当前命令文本的参数串*/
unsigned char AT_GetArgstr(char* order,char* start,char* end,char* argstr)
{
	int slen = strlen(start);
	char *str = strstr(order,start); 
	char *sen=order;
	if(end[0] == 0)
	  sen = order+strlen(order)+1;
	else
	  sen = strstr(order,end);
	
	if((str != NULL) && (sen != NULL))
	{
		char *p = str+slen;
		while(p < sen)
		{
			*argstr++ = *p++;
		}
		*argstr = '\0'; 
		//strcpy(argstr,str+slen+1);
		return 1;
	}
	return 0;

}
/*返回参数串中有几个参?? deli表示分隔??*/
unsigned char AT_ArgNUM(char* argstr,char deli)
{
	int slen = strlen(argstr);
	unsigned char rnum = 1;
	for(int i=0;i<slen;i++)
	{
		if(argstr[i] == deli)
			rnum++;
	}
	return rnum;
}
/*获取分割后的第N个字符串*/
unsigned char AT_GetArgAt(char* argstr,char deli,unsigned char at,char *arg)
{
	int slen = strlen(argstr);
	unsigned char rnum = 0;
	unsigned char len = 0;
	for(int i=0;i<slen;i++)
	{
		if(argstr[i] == deli)
		{
			rnum++;
			continue;
		}
		if(rnum > at) break;
		if(at == rnum)
		{
			if(argstr[i] == '\0')
				break;
			*arg++ = argstr[i];
			len++;
			
		}
		
	}
	*arg = '\0';
	if(rnum >= at) return len;
	else return 0;
	
}



/**
 *    @brief        字符串转int
 *    @param[in]    
 *    @return       
 *    @details       
 */
long int AT_Str2Int(char *source)
{
	int len = strlen(source);
    long int ret = 0;
    int ib=0,fs = 0;;
    for(int i=len-1;i>=0;i--)
    {
        if(source[i] == ' ') continue;//空格不处理
        if((source[i] == '-') && (fs == 0)) 
          fs=1;
        else if((source[i] == '-') && (fs == 1))
          return 0;
        else
        {
            long int tmp = source[i] - '0';
            if((tmp < 0) || (tmp > 9))
            {
                if(ib != 0) return 0;
            }
            else
            {
                for(int i=0;i<ib;i++)
                {
                    tmp*=10;
                }
                ret+=tmp;
                ib++;
            }
        }
        
    }
    if(fs == 1) ret = -ret;
    return ret;
}

/**
 *    @brief        int转字符串
 *    @param[in]    
 *    @return       
 *    @details       
 */
void AT_Int2Str(long int val,char *str)
{
    long int wtmp = val,len=0;;
    char tmp_str[20]={0};
    if(val < 0)
    {
        wtmp = -val;
    }
    do{
        char unit = wtmp%10;
        tmp_str[len] = unit+'0';
        len++;
        wtmp/=10;
    }while(wtmp > 0);
    if(val<0)
    {
        str[0] = '-';
        for(int i=0;i<len;i++)
        {
            str[i+1] = tmp_str[len-1-i];
        }
        str[len+1] = 0;
    }
    else
    {
        for(int i=0;i<len;i++)
        {
            str[i] = tmp_str[len-1-i];
        }
        str[len] = 0;
    }
}
/*double 转字符串 */
void AT_Dob2Str(double val,char *str,char declen)
{
	long int intt = (long int)val;
	AT_Int2Str(intt,str);
	strcat(str,".");
	double tmp = val;
	long int div = 1;
	for(int i=0;i<declen;i++)
	{
		tmp*=10;
		div*=10;
	}
	intt= (long int)tmp%div;
	AT_Int2Str(intt,str+strlen(str));
	
}

/*字符串转double*/
double AT_Str2Dob(char *str)
{
	double ret = 0;
	if(AT_ArgNUM(str,'.')==1)
	{
		ret= AT_Str2Int(str);
	}
	else
	{
		char arg[128];
		AT_GetArgAt(str,'.',0,arg);
		double a = AT_Str2Int(arg);
		AT_GetArgAt(str,'.',1,arg);
		double b = AT_Str2Int(arg);
		int zero_num = 0;
		for(int i=0;arg[i]!=0;i++)
		{
			if(arg[i] == '0')
				zero_num++;
			else
				break;
		}
		while(b>=1) b/=10.0;
		if(zero_num != 0) 
		{
			for(int i=0;i<zero_num;i++)
			{
				b/=10.0;
			}
		}
		int i = 0;
		int fs = 0;
		while(str[i]!=0)
		{
			if(str[i] == '-')
			{
				fs = 1;
				break;
			}
			if(str[i] != ' ')
				break;
		}
		if(fs) ret= (a-b);
		else ret =(a+b);
	}
	return ret;
}
