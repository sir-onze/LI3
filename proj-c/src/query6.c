#include <string.h>
#include <glib.h>
#include <stdio.h>

#include "query6.h"
#include "interface.h"
#include "structures.h"
#include "dateplus.h"
#include "pair.h"
#include "objPost.h"


LONG_list query_6(TAD_community com, int N, Date begin, Date end){

   iterator_aux aux = new_aux();
   set_begin(aux, begin);
   set_end(aux, end);
   int i=0;

   g_hash_table_foreach(get_hash_answers(com), (GHFunc)iterator_6, aux);
   set_q4(aux, g_slist_sort (get_q4(aux),(GCompareFunc)compare_score_posts));
   GSList* lligada = get_q4(aux);
   LONG_list l = create_list(get_q4_cont(aux));


   while (lligada!=NULL && i<N) {
      set_list(l, i, get_post_id(lligada->data));
      i++;
      lligada = lligada->next;
   }
   return l;
}


void iterator_6(gpointer key, gpointer value, iterator_aux aux){

   if( ((long)key > date_to_hashkey(get_begin(aux))) && ((long)key < date_to_hashkey(get_end(aux))) ){
      g_tree_foreach(value,(GTraverseFunc)iterator_6_2, aux);
   }

}

gboolean iterator_6_2(gpointer key, gpointer value, iterator_aux aux){
    if(value!=NULL){
      set_q4(aux, g_slist_prepend(get_q4(aux),value));
      set_q4_cont(aux, get_q4_cont(aux)+1); //linha essencial para criar a nossa llist de retorno
    }
      return FALSE;
}

long compare_score_posts(gconstpointer x, gconstpointer y){
   return (get_post_score((Post)y)-get_post_score((Post)x));
 }
