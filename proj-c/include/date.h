#ifndef __DATE_H__
#define __DATE_H__

typedef struct date* Date;

Date createDate(int day, int month, int year);

int get_day(Date d);

int get_month(Date d);

int get_year(Date d);

void free_date(Date d);

// SETS

void set_year(Date d,int x);
void set_month(Date d,int x);
void set_day(Date d,int x);

#endif
