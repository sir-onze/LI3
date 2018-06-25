#include <string.h>
#include <glib.h>
#include <stdio.h>

#include "query8.h"
#include "interface.h"
#include "structures.h"
#include "dateplus.h"
#include "pair.h"
#include "objPost.h"

LONG_list query_8(TAD_community com, char* word, int N){

   iterator_aux aux = new_aux();
   set_tag(aux,word);
   g_hash_table_foreach(get_hash_questions(com),(GHFunc)iterator_8, aux);
   set_q4(aux, g_slist_sort (get_q4(aux),(GCompareFunc)compare_dates_post));
   GSList* lligada = get_q4(aux);
   LONG_list l = create_list(get_q4_cont(aux));

   int i=0;

   while(lligada!=NULL){
      set_list(l, i, get_post_id(lligada->data));
      i++;
      lligada = lligada->next;
   }

   return l;
}


void iterator_8(gpointer key, gpointer value, iterator_aux aux){
   g_tree_foreach(value,(GTraverseFunc)iterator_8_2, aux);
}

gboolean iterator_8_2(gpointer key, gpointer value, iterator_aux aux){
   if(strstr(get_post_title(value), get_tag(aux))){
      set_q4(aux, g_slist_prepend(get_q4(aux),value));
      set_q4_cont(aux, get_q4_cont(aux)+1);
   }
   return FALSE;
}

long compare_dates_post(gconstpointer x, gconstpointer y){
   return compare_dates_inv(get_post_creation_date((Post)x),get_post_creation_date((Post)y));
}
