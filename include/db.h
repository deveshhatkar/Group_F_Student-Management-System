#pragma once
#ifndef DB_H
#define DB_H

#include "stu.h"

int app_start(char* conf_filename);

void init_env(p_stu_t* stu_list);

#endif // !DB_H
