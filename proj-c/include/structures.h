#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include <glib.h>

#include "interface.h"
#include "list.h"

typedef struct iteratoraux * iterator_aux;

/* FUNÇÕES PRINCIPAIS*/

// Alocamento de memória da nossa estrutura TAD e sub-estruturas
TAD_community new_community();

/* FUNÇÕES AUXILIARES */

// Getters do campos da TAD
GHashTable* get_hash_users(TAD_community com);
GHashTable* get_hash_posts(TAD_community com);
GHashTable* get_hash_questions(TAD_community com);
GHashTable* get_hash_answers(TAD_community Com);
GSList* get_llist_top_users(TAD_community com);
long get_n_questions(TAD_community com);
long get_n_answers(TAD_community com);
Date get_begin(iterator_aux aux);
Date get_end(iterator_aux aux);
long get_questions(iterator_aux aux);
long get_answers(iterator_aux aux);
char* get_tag(iterator_aux aux);
GSList* get_q4(iterator_aux aux);
long get_q4_cont(iterator_aux aux);
TAD_community get_com_aux(iterator_aux aux);


void set_llist_top_users(TAD_community com,GSList* lligada);
void set_n_questions(TAD_community com);
void set_n_answers(TAD_community com);
void set_begin(iterator_aux aux, Date d);
void set_end(iterator_aux aux, Date d);
void set_questions(iterator_aux aux, long q);
void set_answers(iterator_aux aux, long a);
void set_tag(iterator_aux aux, char* tag);
void set_q4(iterator_aux aux, GSList* l);
void set_q4_cont(iterator_aux aux, long a);
void set_com_aux(iterator_aux aux, TAD_community com);

iterator_aux new_aux();

//Função de hash para as nossas hashtables
GHashTable* hashtable_key(long id);
//Função de comparação para as nossas hashtables
gboolean hashtable_equal(gpointer a, gpointer b);

void free_struct_user(gpointer u);
void free_struct_post(gpointer u);
void free_btree_questions(gpointer b);
void free_btree_answers(gpointer b);
#endif
