#pragma once
#ifndef UI_H
#define UI_H

#include <string.h>
#include <stdio.h>

#include "stu.h"
#include "user.h"

void ui_cls();

void ui_pause();

void ui_invalid_prompt();

char ui_get_option();

void route_admin(p_stu_t*);

char ui_get_option();

void ui_init();

void ui_admin();

void ui_stu_query();

void ui_exit();

#endif
