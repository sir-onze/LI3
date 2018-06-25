#ifndef __QUERY_QUATRO__
#define __QUERY_QUATRO__


#include <glib.h>

#include "interface.h"
#include "structures.h"
#include "dateplus.h"
#include "pair.h"


LONG_list query_4(TAD_community com, char* tag, Date begin, Date end);

gboolean iterator_2(gpointer key, gpointer value, iterator_aux aux);
void iterator(gpointer key, gpointer value, iterator_aux aux);
long compare_dates_posts(gconstpointer x, gconstpointer y);

#endif
