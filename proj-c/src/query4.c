
#include <string.h>
#include <glib.h>
#include <stdio.h>

#include "query4.h"
#include "interface.h"
#include "structures.h"
#include "dateplus.h"
#include "pair.h"
#include "objPost.h"


LONG_list query_4(TAD_community com, char* tag, Date begin, Date end){

   int i=0;
   iterator_aux aux = new_aux();
   set_begin(aux, begin);
   set_end(aux, end);
   set_tag(aux, tag);

   g_hash_table_foreach(get_hash_questions(com), (GHFunc)iterator, aux);

   set_q4(aux, g_slist_sort (get_q4(aux),(GCompareFunc)compare_dates_posts));
   GSList* lligada = get_q4(aux);

   LONG_list l = create_list(get_q4_cont(aux));


   while(lligada != NULL){
      set_list(l, i, get_post_id(lligada->data));
      i++;
      lligada = lligada->next;
   }

   return l;
}

void iterator(gpointer key, gpointer value, iterator_aux aux){

   if( ((long)key >= date_to_hashkey(get_begin(aux))) && ((long)key <= date_to_hashkey(get_end(aux))) ){
      g_tree_foreach(value,(GTraverseFunc)iterator_2, aux);
   }
}

gboolean iterator_2(gpointer key, gpointer value, iterator_aux aux){

   if(strstr(get_post_tags(value), get_tag(aux))){
      set_q4(aux, g_slist_prepend(get_q4(aux),value));
      set_q4_cont(aux, get_q4_cont(aux)+1);
   }
   return FALSE;
}

long compare_dates_posts(gconstpointer x, gconstpointer y){
   return compare_dates_inv(get_post_creation_date((Post)x),get_post_creation_date((Post)y));
}
