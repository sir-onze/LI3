#ifndef __QUERY_DOIS__
#define __QUERY_DOIS__


#include "interface.h"
#include "pair.h"


LONG_list query_2(TAD_community com, int N);

void hash_iterator(gpointer key,gpointer value, gpointer com);
long compare_n_posts(gconstpointer x, gconstpointer y);

#endif
