#include <string.h>
#include <glib.h>
#include <stdio.h>

#include "query10.h"
#include "interface.h"
#include "structures.h"
#include "dateplus.h"
#include "pair.h"
#include "objPost.h"
#include "objUser.h"

long query_10(TAD_community com, int id){

    iterator_aux aux = new_aux();
    set_questions(aux,id);
    g_hash_table_foreach(get_hash_answers(com), (GHFunc)iterator_10, aux);
    GSList* lligada = get_q4(aux);
    
    long top=0, aux_top, aux_id;
    int rep;
    User u;

    while(lligada!=NULL){
        
        u=g_hash_table_lookup(get_hash_users(com),(gpointer)get_post_owner_id(lligada->data));
        rep = get_user_reputation(u);
        aux_top=0.65*get_post_score(lligada->data)+0.25*rep+get_posts_comment_count(lligada->data);
        if(aux_top > top){
            top=aux_top;
            aux_id=get_post_id(lligada->data);
        }
        lligada = lligada->next;
    }
    
    return aux_id;
}

void iterator_10(gpointer key, gpointer value, iterator_aux aux){
    g_tree_foreach(value,(GTraverseFunc)iterator_10_2, aux);
}

gboolean iterator_10_2(gpointer key, gpointer value, iterator_aux aux){
    if(get_post_parent_id(value)==get_questions(aux)){
        set_q4(aux, g_slist_prepend(get_q4(aux),value));
        set_q4_cont(aux, get_q4_cont(aux)+1);
    }

    return FALSE;
}
