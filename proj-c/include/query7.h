#ifndef __QUERY_SETE__
#define __QUERY_SETE__

#include "list.h"
#include "interface.h"
#include "dateplus.h"


LONG_list query_7(TAD_community com, int N, Date begin, Date end);

void iterator_7(gpointer key, gpointer value, iterator_aux aux);
gboolean iterator_7_2(gpointer key, gpointer value, iterator_aux aux);
long compare_posts_answers_count(gconstpointer x, gconstpointer y);

void iterator_7_3(gpointer key, gpointer value, iterator_aux aux);
gboolean iterator_7_4(gpointer key, gpointer value, iterator_aux aux);

#endif
