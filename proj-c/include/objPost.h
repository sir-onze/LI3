#ifndef __OBJPOST_H__
#define __OBJPOST_H__

#include "date.h"

typedef struct objPost * Post;

// Construtor parametrizado do objeto Post
Post new_post(long id, int post_type, long owner_id, long parent_id, Date creation_date,
              char* title, char* tags, long score, int answers_count, int comment_count);

// Getters do objeto Post
long get_post_id(Post p);
int get_post_type(Post p);
long get_post_owner_id(Post p);
long get_post_parent_id(Post p);
Date get_post_creation_date(Post p);
char* get_post_title(Post p);
char* get_post_tags(Post p);
long get_post_score(Post p);
int get_posts_answers_count(Post p);
int get_posts_comment_count(Post p);

void set_posts_answers_count(Post p, int n);

// Free
void free_Post(Post p);
#endif
