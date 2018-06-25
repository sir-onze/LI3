



#include <stdlib.h>
#include <stdio.h>

#include "date.h"
#include "dateplus.h"


Date to_date(char* string){

    int i, a=0, m=0, d=0;
    char year[5], month[3], day[3];

    for(i=0; string[i]!='\0'; i++){

        if(i<4){
            year[a]=string[i];
            a++;}
        if(i>4 && i<7){
            month[m]=string[i];
            m++;}
        if(i>7 && i<10){
            day[d]=string[i];
            d++;}
    }
    year[a]='\0'; month[m]='\0'; day[d]='\0';
    Date date = createDate(atoi(day),atoi(month),atoi(year));

    return date;
}

int compare_dates(Date a, Date b){

    int x = get_year(a) - get_year(b);
    if(x) return x;
    x = get_month(a) - get_month(b);
    if(x) return x;
    return get_day(a) - get_day(b);
}

int compare_dates_inv(Date a, Date b){

    int x = get_year(b) - get_year(a);
    if(x) return x;
    x = get_month(b) - get_month(a);
    if(x) return x;
    return get_day(b) - get_day(a);
}

void print_date(Date aux_date){
    printf("d:%d, m:%d, y:%d \n", get_day(aux_date), get_month(aux_date), get_year(aux_date));
}

long date_to_hashkey(Date d){
    return get_year(d)*10000 + get_month(d)*100 + get_day(d);
}

void inc_date(Date d){
    
    int day = get_day(d);
    int month = get_month(d);
    int year = get_year(d);

    if( (day==31)&&(month==12) ){
        year++;
        set_day(d,1);
        set_month(d,1);
    }
    if(month == 2){
        if(day == 29){
            set_day(d,1);
            set_month(d,3);
        }
        if(day == 28){
            if(((year%4 == 0) && (year%100 !=0)) || ((year%400) == 0)){
                 set_day(d,29);
                 set_month(d,2);
            }
            else{
                set_day(d,1);
                set_month(d,3);
            }
        }
	 }
    if(((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10)) && (day == 31)){
        month++;
        set_day(d,1);
    }
    else{
        if(day == 30){
            month++;
            set_day(d,1);
        }
        else{
            day++;
            set_day(d,day);
        }
    }
}
