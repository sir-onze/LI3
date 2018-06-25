#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "query3.h"

#include "user.h"
#include "objUser.h"
#include "interface.h"
#include "structures.h"
#include "dateplus.h"


void iterator_q(gpointer key, gpointer value, iterator_aux aux){

   if( ((long)key > date_to_hashkey(get_begin(aux))) && ((long)key < date_to_hashkey(get_end(aux))) ){
      set_questions(aux, get_questions(aux)+g_tree_nnodes(value));
   }
}

void iterator_a(gpointer key, gpointer value, iterator_aux aux){

   if( ((long)key > date_to_hashkey(get_begin(aux))) && ((long)key < date_to_hashkey(get_end(aux))) ) {
      set_answers(aux, get_answers(aux)+g_tree_nnodes(value));
   }
}

LONG_pair query_3(TAD_community com, Date begin, Date end){

   long questions=0, answers=0;
   iterator_aux aux = new_aux();
   set_begin(aux, begin);
   set_end(aux, end);
   LONG_pair pair = create_long_pair(0, 0);

   g_hash_table_foreach(get_hash_questions(com), (GHFunc)iterator_q, aux);
   g_hash_table_foreach(get_hash_answers(com), (GHFunc)iterator_a, aux);

  set_fst_long(pair, questions);
  set_snd_long(pair, answers);
  return pair;
}
