//C/C++
#include <stdio.h>
#include <time.h>

// 某日前N日的日期
char *GetBeforeDate(char *start_date, int days)
{
    static char str[10];
    struct tm tm1;
    char tmp[10];
    time_t t1;
    struct tm *tm2;

    strncpy(tmp, start_date, 4);
    tmp[4]=0;
    tm1.tm_year=atoi(tmp) - 1900;
    strncpy(tmp, start_date+4, 2);
    tmp[2] = 0;
    tm1.tm_mon = atoi(tmp)-1;
    strncpy(tmp, start_date+6, 2);
    tmp[2] = 0;
    tm1.tm_mday = atoi(tmp);
    tm1.tm_hour = 0;
    tm1.tm_min = 0;
    tm1.tm_sec = 1;
    tm1.tm_isdst = -1;
    t1 = mktime(&tm1);
    t1 = t1 - days*24*3600;
    tm2 = localtime(&t1);
    sprintf(str,"%04d%02d%02d", tm2->tm_year+1900, tm2->tm_mon+1, tm2->tm_mday);
    return str;
}

// 某日之后N日的日期
char *GetAfterDate(char *start_date, int days)
{
    static char str[10];
    struct tm tm1;
    char tmp[10];
    time_t t1;
    struct tm *tm2;

    strncpy(tmp, start_date, 4);
    tmp[4]=0;
    tm1.tm_year=atoi(tmp) - 1900;
    strncpy(tmp, start_date+4, 2);
    tmp[2]=0;
    tm1.tm_mon=atoi(tmp)-1;
    strncpy(tmp, start_date+6, 2);
    tmp[2]=0;
    tm1.tm_mday=atoi(tmp);
    tm1.tm_hour = 0;
    tm1.tm_min = 0;
    tm1.tm_sec = 1;
    tm1.tm_isdst = -1;
    t1 = mktime(&tm1);
    t1 = t1 + days*24*3600;
    tm2 = localtime(&t1);
    sprintf(str,"%04d%02d%02d", tm2->tm_year+1900, tm2->tm_mon+1, tm2->tm_mday);
    return str;
}


// 日期差
long DateDiff(char *s0,char *s1)
{
	struct tm tm1;
	struct tm tm2;
	char tmp[10];
	time_t t1,t2;

	strncpy(tmp, s0, 4);
	tmp[4] = 0;
	tm1.tm_year = atoi(tmp)-1900;
	strncpy(tmp, s0+4, 2);
	tmp[2] = 0;
	tm1.tm_mon = atoi(tmp)-1;
	strncpy(tmp, s0+6, 2);
	tmp[2] = 0;
	tm1.tm_mday = atoi(tmp);
	tm1.tm_hour = 0;
	tm1.tm_min = 0;
	tm1.tm_sec = 1;
	tm1.tm_isdst = -1;
	t1= mktime(&tm1);

	strncpy(tmp, s1, 4);
	tmp[4]=0;
	tm2.tm_year = atoi(tmp) - 1900;
	strncpy(tmp, s1+4, 2);
	tmp[2] = 0;
	tm2.tm_mon = atoi(tmp)-1;
	strncpy(tmp, s1+6, 2);
	tmp[2] = 0;
	tm2.tm_mday = atoi(tmp);
	tm2.tm_hour = 0;
	tm2.tm_min = 0;
	tm2.tm_sec = 1;
	tm2.tm_isdst = -1;
	t2 = mktime(&tm2);
	return (t2-t1)/24/60/60;
}

// 检查日期有效性
bool IsDate(char *sInputDate)
{
    struct tm tm1;
    struct tm *tm2;
    char tmp[10],sOutputDate[10];
    time_t t1;
    long  ndaytime;
    if (strlen(sInputDate) != 8) return false;

    strncpy(tmp, sInputDate, 4);
    tmp[4] = 0;
    tm1.tm_year = atoi(tmp) - 1900;
    strncpy(tmp, sInputDate+4, 2);
    tmp[2] = 0;
    tm1.tm_mon = atoi(tmp)-1;
    strncpy(tmp, sInputDate+6, 2);
    tmp[2] = 0;
    tm1.tm_mday = atoi(tmp);
    tm1.tm_hour = 0;
    tm1.tm_min = 0;
    tm1.tm_min = 0;
    tm1.tm_sec = 1;
    tm1.tm_isdst = -1;
    t1 = mktime(&tm1);
    tm2 = localtime(&t1);
    sprintf(sOutputDate, "%04d%02d%02d", tm2->tm_year+1900, tm2->tm_mon+1, tm2->tm_mday);
    if (strcmp(sOutputDate, sInputDate)==0)
        return true;

    return false;
}
