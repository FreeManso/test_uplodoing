#ifndef __ATORDER_H__
#define __ATORDER_H__

unsigned char AT_IsOrder(char* head,char* end,char* order);
unsigned char AT_IncOrder(char* ins,char* order);
unsigned char AT_GetIns(char* order,char head,char end,char* ins);
unsigned char AT_GetArgstr(char* order,char* start,char* end,char* argstr);
unsigned char AT_ArgNUM(char* argstr,char deli);
unsigned char AT_GetArgAt(char* argstr,char deli,unsigned char at,char *arg);

long int AT_Str2Int(char *source);
void AT_Int2Str(long int val,char *str);
void AT_Dob2Str(double val,char *str,char declen);

double AT_Str2Dob(char *str);









#endif /* __ATORDER_H__ */
