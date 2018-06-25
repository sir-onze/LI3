
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "interface.h"
#include "structures.h"
#include "objUser.h"
#include "objPost.h"
#include "common.h"
#include "dateplus.h"

struct objUser{

    long id;
    char* name;
    int reputation;
    char* s_bio;
    long n_posts;
    GSList* posts;
};

User new_user(long id, int reputation, char* name, char* s_bio, long n_posts, GSList* posts){

    User u = malloc(sizeof(struct objUser));

    u->id = id;
    u->name = mystrdup(name);
    u->reputation= reputation;
    u->s_bio = mystrdup(s_bio);
    u->n_posts = n_posts;
    u->posts = posts;

    return u;
}

long get_user_id(User u){
    if(u)
        return u->id;
    return -2;}

int get_user_reputation(User u){
    if(u)
        return u->reputation;
    return -2;}

char* get_user_name(User u){
    if(u)
        return u->name;
    return NULL;}

char* get_user_s_bio(User u){
    if(u)
        return u->s_bio;
    return NULL;}

long get_user_n_posts(User u){
    if(u)
        return u->n_posts;
    return -2;}

GSList* get_user_posts(User u){
    if(u)
        return u->posts;
    return NULL;}

void set_user_posts(User u, GSList* lligada){
	u->posts = lligada;
}

void inc_user_n_posts(User u){
    (u->n_posts)++;}

void update_user_posts(TAD_community com, Post p){
	User u = g_hash_table_lookup(get_hash_users(com), (gpointer)get_post_owner_id(p));
	if( u!=NULL )
        u->posts = g_slist_prepend(u->posts, p);
}

void free_User(User u){

    if(u){
        free(u->name);
        free(u->s_bio);
        g_slist_free(u->posts);

        free(u);
    }
}
