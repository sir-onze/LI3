#ifndef __QUERY_SEIS__
#define __QUERY_SEIS__

#include <glib.h>

#include "interface.h"
#include "structures.h"
#include "dateplus.h"
#include "pair.h"


LONG_list query_6(TAD_community com, int N, Date begin, Date end);
void iterator_6(gpointer key, gpointer value, iterator_aux aux);
gboolean iterator_6_2(gpointer key, gpointer value, iterator_aux aux);
long compare_score_posts(gconstpointer x, gconstpointer y);

#endif
