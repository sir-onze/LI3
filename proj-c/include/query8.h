#ifndef __QUERY_OITO__
#define __QUERY_OITO__

#include <glib.h>

#include "interface.h"
#include "structures.h"
#include "dateplus.h"
#include "pair.h"

LONG_list query_8(TAD_community com, char* word, int N);

void iterator_8(gpointer key, gpointer value, iterator_aux aux);

gboolean iterator_8_2(gpointer key, gpointer value, iterator_aux aux);

long compare_dates_post(gconstpointer x, gconstpointer y);

#endif
