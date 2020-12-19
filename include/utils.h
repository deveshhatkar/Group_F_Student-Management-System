// Todo: Doxygen Main Page and comments

// utils.h
// Siyuan Chen 
// Dec.16, 2020

#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#include "stu.h"
#include "user.h"
#include "ui.h"

//STUB
#define _type_account_admin 0
#define _type_account_student 1

//STUB
char* account_type_tostring(int type);

int ask_for_input(char* _to_print, bool bound_enable, int lower_bound, int upper_bound);

char* string_input(char* output, int max_length);

#endif