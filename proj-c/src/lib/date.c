#include <stdlib.h>
#include "date.h"

struct date {
  int day;
  int month;
  int year;
};

Date createDate(int day, int month, int year) {
    Date d = malloc(sizeof(struct date));
    d->day = day;
    d->month = month;
    d->year = year;
    return d;
}

int get_day(Date d) {
    return d->day;
}

int get_month(Date d) {
    return d->month;
}

int get_year(Date d) {
    return d->year;
}

void free_date(Date d) {
    free(d);
}

void set_year(Date d,int x){
	d->year=x;
}

void set_month(Date d,int x){
	d->month=x;
}

void set_day(Date d,int x){
	d->day=x;
}
