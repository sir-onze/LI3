

#include <stdio.h>

#include "pair.h"
#include "query1.h"

#include "interface.h"
#include "structures.h"
#include "objUser.h"
#include "objPost.h"



STR_pair query_1(TAD_community com, long id){

	User u;Post p;
	char *title = "", *username = "";
	long parent_id;
	STR_pair pair = create_str_pair(title,username);

	p = g_hash_table_lookup(get_hash_posts(com), (gpointer)id);
	long owner_id;

	if(get_post_type(p) == 1){
		title = get_post_title(p);
		owner_id = get_post_owner_id(p);
		u = g_hash_table_lookup(get_hash_users(com), (gpointer)owner_id);
		username = get_user_name(u);
	}

	if(get_post_type(p) == 2){
		parent_id = get_post_parent_id(p);
		p = g_hash_table_lookup(get_hash_posts(com), (gpointer)parent_id);
		title = get_post_title(p);
		owner_id = get_post_owner_id(p);
		u = g_hash_table_lookup(get_hash_users(com), (gpointer)owner_id);
		username = get_user_name(u);
	}

	set_fst_str(pair,title);
	set_snd_str(pair,username);

    return pair;
}
