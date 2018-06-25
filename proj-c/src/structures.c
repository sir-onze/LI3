
#include <stdlib.h>
#include <glib.h>

#include "structures.h"
#include "objUser.h"
#include "objPost.h"
#include "date.h"
#include "list.h"

struct iteratoraux{
		  
		  Date begin;
		  Date end;
		  long questions, answers;
		  char* tag;
		  GSList* q4;
		  long q4_cont;
		  
		  TAD_community com;
};

struct TCD_community{
		  
		  GHashTable* users;
		  GHashTable* posts;
		  GHashTable* questions;
		  GHashTable* answers;
		  
		  GSList* top_users;
};

iterator_aux new_aux(){

    iterator_aux aux = malloc(sizeof(struct iteratoraux));

    aux->questions = 0;
    aux->answers = 0;
    aux->q4 = NULL;
    aux->q4_cont = 0;
    aux->com = NULL;
    
    return aux;
}

TAD_community new_community(){
		  
		  TAD_community com = malloc(sizeof(struct TCD_community));
		  
		  com->users = g_hash_table_new_full( (GHashFunc)hashtable_key, (GEqualFunc)hashtable_equal, NULL, (GDestroyNotify)free_struct_user);
		  com->posts = g_hash_table_new_full( (GHashFunc)hashtable_key, (GEqualFunc)hashtable_equal, NULL, (GDestroyNotify)free_struct_post);
		  com->questions = g_hash_table_new_full( (GHashFunc)hashtable_key, (GEqualFunc)hashtable_equal, NULL, (GDestroyNotify)free_btree_questions);
		  com->answers = g_hash_table_new_full( (GHashFunc)hashtable_key, (GEqualFunc)hashtable_equal, NULL, (GDestroyNotify)free_btree_answers);
		  
		  return com;
}

/* GETTERS DA TCD COMMUNITY */
GHashTable* get_hash_users(TAD_community com){
		  return com->users;}
GHashTable* get_hash_posts(TAD_community com){
		  return com->posts;}
GHashTable* get_hash_questions(TAD_community com){
		  return com->questions;}
GHashTable* get_hash_answers(TAD_community com){
		  return com->answers;}
GSList* get_llist_top_users(TAD_community com){
		  return com->top_users;}

/* SETTERS DA TCD COMMUNITY */
void set_llist_top_users(TAD_community com, GSList* lligada){
		  com->top_users=lligada;}

/* FUNCOES PARA A NEW HASH */
GHashTable* hashtable_key(long id){
		  return (gpointer)id;}

gboolean hashtable_equal(gpointer a, gpointer b){
		  if( a==b ) return TRUE;
		  else return FALSE;}

/* GETTERS DA ITERATOR AUX */
Date get_begin(iterator_aux aux){
		  return aux->begin;}
Date get_end(iterator_aux aux){
		  return aux->end;}
long get_questions(iterator_aux aux){
		  return aux->questions;}
long get_answers(iterator_aux aux){
		  return aux->answers;}
char* get_tag(iterator_aux aux){
		  return aux->tag;}
GSList* get_q4(iterator_aux aux){
		  return aux->q4;}
long get_q4_cont(iterator_aux aux){
		  return aux->q4_cont;}
TAD_community get_com_aux(iterator_aux aux){
		  return aux->com;}

/* SETTERS DA ITERATOR AUX */
void set_begin(iterator_aux aux, Date d){
		  aux->begin=d;}
void set_end(iterator_aux aux, Date d){
		  aux->end=d;}
void set_questions(iterator_aux aux, long q){
		  aux->questions=q;}
void set_answers(iterator_aux aux, long a){
		  aux->answers=a;}
void set_tag(iterator_aux aux, char* tag){
		  aux->tag=tag;}
void set_q4(iterator_aux aux, GSList* l){
		  aux->q4=l;}
void set_q4_cont(iterator_aux aux, long a){
		  aux->q4_cont=a;}
void set_com_aux(iterator_aux aux, TAD_community com){
		  aux->com = com;}

/* FUNCOES PARA FREE DAS STRUCTS */
void free_struct_user(gpointer u){
		  free_User((User)u);}

void free_struct_post(gpointer p){
		  free_Post((Post)p);}

void free_btree_questions(gpointer b){
		  g_tree_destroy(b);}

void free_btree_answers(gpointer b){
		  g_tree_destroy(b);}
