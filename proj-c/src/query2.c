
#include <glib.h>
#include <stdio.h>

#include "query2.h"

#include "objUser.h"
#include "interface.h"
#include "pair.h"
#include "structures.h"



LONG_list query_2(TAD_community com, int N){

   g_hash_table_foreach(get_hash_users(com), (GHFunc)hash_iterator, com);

   GSList* top_users = get_llist_top_users(com), *curr;
   top_users = g_slist_sort(top_users, (GCompareFunc)compare_n_posts);
   curr = top_users;

   for(int i = 0; i < N; i++)
      curr = curr->next;

   top_users = g_slist_delete_link(top_users, curr);

   curr = top_users;
   
    return (LONG_list)top_users;
}

void hash_iterator(gpointer key,gpointer value, gpointer com){
   GSList* aux = get_llist_top_users(com);
   aux = g_slist_prepend(aux,value);
   set_llist_top_users(com, aux);
}

long compare_n_posts(gconstpointer x, gconstpointer y){
   return get_user_n_posts((User)y)-get_user_n_posts((User)x);
}
