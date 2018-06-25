
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "query5.h"

#include "user.h"
#include "objUser.h"
#include "interface.h"
#include "structures.h"
#include "dateplus.h"

USER query_5(TAD_community com, long id){

  long array_posts[10];
  USER user;

  User u = g_hash_table_lookup(get_hash_users(com), (gpointer)id);
  set_user_posts(u, g_slist_sort(get_user_posts(u), (GCompareFunc)compare_dates_inv));
  GSList* posts = get_user_posts(u), *curr;
  curr = posts;

  for(int i = 0; i<10; i++){
    array_posts[i] = get_post_id(curr->data);
    curr = curr->next;
  }

  user = create_user(get_user_s_bio(u),array_posts);

  return user;
}
