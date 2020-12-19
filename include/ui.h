#pragma once
#ifndef UI_H
#define UI_H

#include <string.h>
#include <stdio.h>

#include "stu.h"
#include "user.h"

#define CLEAR_BUF \
    {\
    int ch; \
while ((ch = getchar()) != EOF && ch != '\n')\
        {\
        ; \
        }\
    }



void get_pass(char* password);

void route_admin(p_user_t*, p_stu_t*, char*, char*);

void route_guest(p_stu_t);

void ui_init();

void ui_admin();

void ui_guest();

void ui_stu_query(int);

void ui_user_query(p_user_t);

void ui_exit();

#endif
