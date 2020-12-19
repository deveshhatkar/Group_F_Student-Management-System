#pragma once
#ifndef DB_H
#define DB_H

#include "stu.h"
#include "user.h"

int app_start(char* conf_file_path);

void init_env(p_stu_t* stu_list, p_user_t* user_list);

void studb_update(p_stu_t* stu_list, char* str);

void userdb_update(p_user_t* user_list, char* str);

#endif // !DB_H
