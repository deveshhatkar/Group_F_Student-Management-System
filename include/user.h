#pragma once
#ifndef USER_H
#define USER_H

#define USER_NAME_MAXLEN 20
#define USER_PASS_MAXLEN 8

enum { ADMIN, GUEST };

typedef struct user {
	char name[USER_NAME_MAXLEN + 1];
	char pass[USER_PASS_MAXLEN + 1];
	int type;
	struct user* next;
}user_t, * p_user_t;

int user_auth(p_user_t, user_t);



void user_query(p_user_t);

void user_query_listall(p_user_t);

void user_query_by_level(p_user_t);

void user_query_by_name(p_user_t);

void user_add(p_user_t*, char*);

void user_update(p_user_t*, char*);

void user_del(p_user_t*, char*);

#endif