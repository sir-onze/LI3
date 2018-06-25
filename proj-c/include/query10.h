#ifndef __QUERY_DEZ__
#define __QUERY_DEZ__

#include <glib.h>

#include "interface.h"
#include "structures.h"
#include "dateplus.h"
#include "pair.h"

long query_10(TAD_community com, int id);
void iterator_10(gpointer key, gpointer value, iterator_aux aux);
gboolean iterator_10_2(gpointer key, gpointer value, iterator_aux aux);

#endif
