
#include <stdlib.h>

#include "objPost.h"
#include "common.h"



struct objPost{

    long id, owner_id, parent_id;
    int post_type;
    Date creation_date;
    char* title;
    char* tags;
    long score;
    
    int answers_count;
    int comment_count;
};

Post new_post(long id, int post_type, long owner_id, long parent_id, Date creation_date,
				  char* title, char* tags, long score, int answers_count, int comment_count){

    Post p = malloc(sizeof(struct objPost));

    p->id = id;
    p->post_type = post_type;
    p->owner_id = owner_id;
    p->parent_id = parent_id;
    p->creation_date = creation_date;
    p->title = mystrdup(title);
    p->tags = mystrdup(tags);
    p->score = score;
    p->answers_count = answers_count;
    p->comment_count = comment_count;

    return p;
}

long get_post_id(Post p){
    if(p)
        return p->id;
    return -2;}

int get_post_type(Post p){
    if(p)
        return p->post_type;
    return -2;}

long get_post_owner_id(Post p){
    if(p)
        return p->owner_id;
    return -2;}

long get_post_parent_id(Post p){
    if(p)
        return p->parent_id;
    return -2;}

Date get_post_creation_date(Post p){
    if(p)
        return p->creation_date;
    return NULL;}

char* get_post_title(Post p){
    if(p)
        return p->title;
    return NULL;}

char* get_post_tags(Post p){
    if(p)
        return p->tags;
    return NULL;}

long get_post_score(Post p){
    if(p)
        return p->score;
    return -2;}

int get_posts_answers_count(Post p){
    if(p)
        return p->answers_count;
    return -2;}

int get_posts_comment_count(Post p){
    if(p)
        return p->comment_count;
    return -2;}

void set_posts_answers_count(Post p, int n){
    p->answers_count = n;}

void free_Post(Post p){
	if(p){
        free_date(p->creation_date);
        free(p->title);
        free(p->tags);
        free(p);
    }
}
