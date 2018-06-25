#ifndef __PARSER_H__
#define __PARSER_H__


#include <glib.h>

#include "objPost.h"



/* FUNÇÕES PRINCIPAIS */

// Parse do XML dos Users (Leitura e carregamento nas estruturas)
int parse_xmlusers(GHashTable* HashUsers, char* dump_path_users);
// Parse do XML dos Posts (Leitura e carregamento nas estruturas)
int parse_xmlposts(TAD_community com, char* dump_path_posts);


/* FUNÇÕES AUXILIARES */

// GCompareFunc da BTree
long compare_ids(gconstpointer x, gconstpointer y);

// Nova BTree com inserção do objeto P
GTree* new_btree(Post p);

#endif
