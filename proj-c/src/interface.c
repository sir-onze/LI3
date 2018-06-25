
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "parser.h"
#include "structures.h"
#include "common.h"
#include "dateplus.h"

#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "query4.h"
#include "query5.h"
#include "query6.h"
#include "query7.h"
#include "query8.h"
#include "query10.h"


TAD_community init(){
    return new_community();}

TAD_community load(TAD_community com, char* dump_path){
    
    char* aux_users = malloc(sizeof(char)*128);
    char* aux_posts = malloc(sizeof(char)*128);
    strcpy(aux_users,dump_path);
    strcpy(aux_posts,dump_path);

    if((parse_xmlusers(get_hash_users(com), strcat(aux_users,"/Users.xml")) == -2))
        printf("Error parsing ...");
    if((parse_xmlposts(com, strcat(aux_posts,"/Posts.xml"))) == -2)
        printf("Error parsing ...");

    free(aux_users);
    free(aux_posts);

    return com;}

STR_pair info_from_post(TAD_community com, long id){
    return query_1(com, id);
}

LONG_list top_most_active(TAD_community com, int N){
    return query_2(com, N);
}

LONG_pair total_posts(TAD_community com, Date begin, Date end){
    return query_3(com,begin,end);
}

LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
    return query_4(com, tag, begin, end);
}

USER get_user_info(TAD_community com, long id){
    return query_5(com, id);
}

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
    return query_6(com, N, begin, end);
}

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
    return query_7(com, N, begin, end);
}

LONG_list contains_word(TAD_community com, char* word, int N){
    return query_8(com, word, N);
}

long better_answer(TAD_community com, long id){
    return query_10(com,id);
}

TAD_community clean(TAD_community com){
	
    g_hash_table_destroy(get_hash_users(com));
    g_hash_table_destroy(get_hash_posts(com));
    g_hash_table_destroy(get_hash_questions(com));
    g_hash_table_destroy(get_hash_answers(com));

    free(com);

    return NULL;
}
