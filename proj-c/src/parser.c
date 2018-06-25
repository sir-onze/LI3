

#include </usr/include/libxml2/libxml/tree.h>
#include </usr/include/libxml2/libxml/parser.h>

#include "interface.h"
#include "structures.h"
#include "parser.h"
#include "dateplus.h"
#include "objUser.h"
#include "objPost.h"

int parse_xmlusers(GHashTable* users, char* dump_path_users){

    xmlChar *attr_id=NULL, *attr_bio=NULL, *attr_rep=NULL, *attr_dispname=NULL;
    User u;long id;int reputation;char *name, *s_bio;

    xmlDocPtr doc = xmlParseFile(dump_path_users);

    if(doc == NULL){
        fprintf(stderr,"Document not parsed successfully. \n");
        return -2;}

    xmlNodePtr cur = xmlDocGetRootElement(doc);
    if(cur == NULL){
        fprintf(stderr,"Empty Document\n");
        xmlFreeDoc(doc);
        return -2;}

    cur = cur->xmlChildrenNode;
    while(cur!=NULL){
        if( (!xmlStrcmp(cur->name, (const xmlChar *)"row")) ){

            attr_id = xmlGetProp(cur, (const xmlChar *)"Id");
            attr_rep = xmlGetProp(cur, (const xmlChar *)"Reputation");
            attr_dispname = xmlGetProp(cur, (const xmlChar *)"DisplayName");
            attr_bio = xmlGetProp(cur, (const xmlChar *)"AboutMe");

            /* ID */
            id = atol((char*)attr_id);
            /* REP */
            if( attr_rep!=NULL )
                reputation = atoi((char*)attr_rep);
            else
                reputation = 0;
            /* DISPNAME */
            if( attr_dispname!=NULL )
                name = (char*)attr_dispname;
            /* BIO */
            if( attr_bio!=NULL )
                s_bio = (char*)attr_bio;
            // CRIAÇÃO DO OBJETO USER U
            if(id>0){
                u = new_user(id, reputation, name, s_bio, 0, NULL);
                g_hash_table_insert(users, (gpointer) id, (gpointer) u);
            }
			xmlFree(attr_id);
            xmlFree(attr_rep);
            xmlFree(attr_dispname);
            xmlFree(attr_bio);
        }
        cur=cur->next;
    }
    xmlFreeDoc(doc);

    return 0;
}

int parse_xmlposts(TAD_community com, char* dump_path_posts){

    xmlChar *attr_ownerid=NULL, *attr_id=NULL, *attr_posttype=NULL;
    xmlChar *attr_parentid=NULL, *attr_date=NULL, *attr_title=NULL;
    xmlChar *attr_tags=NULL, *attr_score=NULL, *attr_ccount=NULL;

    Post p;User u;
    long id, owner_id, parent_id, score;
    int post_type, comment_count;
    Date creation_date;
    char *title, *tags;

    xmlDocPtr doc = xmlParseFile(dump_path_posts);
    if( doc==NULL ){
        fprintf(stderr,"Document not parsed successfully. \n");
        return -2;}
    xmlNodePtr cur = xmlDocGetRootElement(doc);
    if( cur==NULL ){
        fprintf(stderr,"Empty Document\n");
        xmlFreeDoc(doc);return -2;}

    cur = cur->xmlChildrenNode;
    while(cur!=NULL){
        if((!xmlStrcmp(cur->name, (const xmlChar *)"row"))){

            attr_ownerid = xmlGetProp(cur, (const xmlChar *)"OwnerUserId");
            attr_id = xmlGetProp(cur, (const xmlChar *)"Id");
            attr_posttype = xmlGetProp(cur, (const xmlChar *)"PostTypeId");
            attr_date = xmlGetProp(cur, (const xmlChar *)"CreationDate");
            attr_title = xmlGetProp(cur, (const xmlChar *)"Title");
            attr_tags = xmlGetProp(cur, (const xmlChar *)"Tags");
            attr_score = xmlGetProp(cur, (const xmlChar *)"Score");
            attr_ccount = xmlGetProp(cur, (const xmlChar *)"CommentCount");

            /* verificação se posts tem owner id e não é o default */
            if( ( attr_ownerid!=NULL )&&(atol((char*)attr_id)!=-1) ){

                /* OWNERID */
                owner_id = atol((char*)attr_ownerid);
                /* ID */
                id = atol((char*)attr_id);
                /* POST TYPE e PARENT ID POR ARRASTO */
                post_type = atoi((char*)attr_posttype);
                if( post_type==2 ){
                    attr_parentid = xmlGetProp(cur, (const xmlChar *)"ParentId");
                    parent_id = atol((char*)attr_parentid);
                }
                if( post_type==1 ){
                    parent_id = 0;
                }
                else{
                    post_type = 0;
                    parent_id = 0;
                }
                /* CREATION DATE */
                creation_date = to_date((char*)attr_date);
                /* TITLE */
                title = (char*)attr_title;
                /* TAGS */
                tags = (char*)attr_tags;
                /* SCORE */
                if( attr_score==NULL )
                    score = 0;
                else
                    score = atol((char*)attr_score);
                /* COMMENT_COUNT */
                if( attr_ccount==NULL )
                    comment_count = 0;
                else
                    comment_count = atoi((char*)attr_ccount);
				
                /* CRIAÇÃO DO OBJETO POST P */
                p = new_post(id, post_type, owner_id, parent_id, creation_date, title, tags, score, 0, comment_count);

                /* INC DO CAMPO N_POSTS DO RESPETIVO USER */
                u = g_hash_table_lookup(get_hash_users(com), (gpointer)owner_id);
                if( u!=NULL )
                    inc_user_n_posts(u);
                /* INSERÇÃO NO CAMPO POSTS DO RESPETIVO USER */
                update_user_posts(com, p);
                /* INSERÇÃO NA HASHTABLE GERAL DOS POSTS */
                g_hash_table_insert(get_hash_posts(com), (gpointer) id, (gpointer) p);

                /* CASO SEJA UMA PERGUNTA */
                if(post_type == 1){
                    if(g_hash_table_lookup(get_hash_questions(com), (gpointer)date_to_hashkey(get_post_creation_date(p))) == NULL)
                        g_hash_table_insert(get_hash_questions(com), (gpointer)date_to_hashkey(get_post_creation_date(p)), (gpointer)new_btree(p));
                    else{
                        g_tree_insert(
                                g_hash_table_lookup(
                                    get_hash_questions(com), (gpointer)date_to_hashkey(get_post_creation_date(p))), (gpointer) id, (gpointer) p);
                    }
                }
                /* CASO SEJA UMA RESPOSTA */
                if(post_type == 2){
                    if(g_hash_table_lookup(get_hash_answers(com), (gpointer)date_to_hashkey(get_post_creation_date(p))) == NULL)
                        g_hash_table_insert(get_hash_answers(com), (gpointer)date_to_hashkey(get_post_creation_date(p)), (gpointer)new_btree(p));
                    else{
                        g_tree_insert(
                                g_hash_table_lookup(
                                    get_hash_answers(com), (gpointer)date_to_hashkey(get_post_creation_date(p))), (gpointer) id, (gpointer) p);
                    }
                }
            }
        }
        cur=cur->next;
	}
    
    xmlFree(attr_id);
    xmlFree(attr_ownerid);
    xmlFree(attr_posttype);
    xmlFree(attr_date);
    xmlFree(attr_title);
    xmlFree(attr_tags);
    xmlFree(attr_score);
    xmlFree(attr_ccount);
    
    xmlFreeDoc(doc);

	return 0;
}

long compare_ids(gconstpointer x, gconstpointer y){
    return x-y;}

GTree* new_btree(Post p){
    GTree* bt_node = g_tree_new_full((GCompareDataFunc)compare_ids, NULL, NULL, (GDestroyNotify)free_Post);
    g_tree_insert(bt_node, (gpointer)get_post_id(p), p);
    return bt_node;}
