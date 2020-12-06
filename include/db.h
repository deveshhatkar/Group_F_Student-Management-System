#pragma once
#ifndef DB_H
#define DB_H

#include "user.h"
#include "stu.h"

int app_start(char* conf_filename);

void init_env(p_user_t* user_list, p_stu_t* stu_list, char* str1, char* str2);

void studb_update(p_stu_t*, char*);

void userdb_update(p_user_t*, char*);

#endif // !DB_H
