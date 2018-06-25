
#include <glib.h>
#include <stdio.h>

#include "list.h"
#include "interface.h"
#include "structures.h"
#include "dateplus.h"
#include "objPost.h"
#include "query7.h"


LONG_list query_7(TAD_community com, int N, Date begin, Date end){

   iterator_aux aux = new_aux();
   set_begin(aux, begin);
   set_end(aux, end);
   set_com_aux(aux, com);
   int i=0;

   g_hash_table_foreach(get_hash_answers(com), (GHFunc)iterator_7, aux);
   g_hash_table_foreach(get_hash_questions(com), (GHFunc)iterator_7_3, aux);

   set_q4(aux, g_slist_sort (get_q4(aux),(GCompareFunc)compare_posts_answers_count));
   GSList* lligada = get_q4(aux);
   LONG_list l = create_list(N);

   while (lligada!=NULL && i<N) {
      set_list(l, i, get_post_id(lligada->data));
      i++;
      lligada = lligada->next;
   }
   return l;
}


void iterator_7(gpointer key, gpointer value, iterator_aux aux){

   if( ((long)key > date_to_hashkey(get_begin(aux))) && ((long)key < date_to_hashkey(get_end(aux))) ){
      g_tree_foreach(value,(GTraverseFunc)iterator_7_2, aux);
   }
}

gboolean iterator_7_2(gpointer key, gpointer value, iterator_aux aux){
    if(value!=NULL){
      Post p = g_hash_table_lookup(get_hash_posts(get_com_aux(aux)), (gpointer)get_post_parent_id(value));
      if(p != NULL)  set_posts_answers_count(p, get_posts_answers_count(p)+1);
    }
      return FALSE;
}

void iterator_7_3(gpointer key, gpointer value, iterator_aux aux){

   if( ((long)key > date_to_hashkey(get_begin(aux))) && ((long)key < date_to_hashkey(get_end(aux))) ){
      g_tree_foreach(value,(GTraverseFunc)iterator_7_4, aux);
   }
}

gboolean iterator_7_4(gpointer key, gpointer value, iterator_aux aux){
    if(value!=NULL){
      set_q4(aux, g_slist_prepend(get_q4(aux),value));
    }
    return FALSE;
}

long compare_posts_answers_count(gconstpointer x, gconstpointer y){
   return (get_posts_answers_count((Post)y)-get_posts_answers_count((Post)x));
}
