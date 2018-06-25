#ifndef __DATE2_H__
#define __DATE2_H__

#include "date.h"

// CAMPO DO XML PARA TIPO ABSTRATO Date
Date to_date(char* string);

// GCompareFunc PARA DAtAS (ORDEm CRESCENTE)
int compare_dates(Date a, Date b);

// GCompareFunc PARA DAtAS (ORDEM DECRESCENTE)
int compare_dates_inv(Date a, Date b);

// PRINT DOS CAMPOS DA STRUCT Date
void print_date(Date aux_date);

// STRUCT Date d PARA UMA HASHKEY UNICA
long date_to_hashkey(Date d);

// INCREMENTO EM 1 DIA A DATA d
void inc_date(Date d);

#endif
