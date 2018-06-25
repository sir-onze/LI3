#ifndef __QUERY_TRES__
#define __QUERY_TRES__

#include "interface.h"
#include "pair.h"
#include "dateplus.h"
#include "structures.h"


LONG_pair query_3(TAD_community com, Date begin, Date end);
void iterator_q(gpointer key, gpointer value, iterator_aux aux);
void iterator_a(gpointer key, gpointer value, iterator_aux aux);

#endif
