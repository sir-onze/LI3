#ifndef __OBJUSER_H__
#define __OBJUSER_H__

#include "objPost.h"
#include <glib.h>


typedef struct objUser * User;

// Construtor parametrizado do objeto User
User new_user(long id, int reputation, char* name, char* s_bio, long n_posts, GSList* posts);

// Getters do objeto User
long get_user_id(User u);
int get_user_reputation(User u);
char* get_user_name(User u);
char* get_user_s_bio(User u);
long get_user_n_posts(User u);
GSList* get_user_posts(User u);

void set_user_posts(User u, GSList* lligada);

void update_user_posts(TAD_community com, Post p);

void inc_user_n_posts(User u);


// Free
void free_User(User u);
#endif
