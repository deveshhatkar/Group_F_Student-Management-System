/** @file utils.h
 * 
 * \brief Internal functions as Utilities
 * 
 * utils.h
 * Internal functions as Utilities. 
 * 
 * @author Siyuan Chen
 * 
 */

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


#define _type_account_admin 0
#define _type_account_student 1


/** @brief return the account type in string based on type integer defined in the struct.
 * 
 * account_type_tostring: 
 * @param type int: 0 to return "Admin", 1 to return "Student"
 * @return the string identified above
 */
char* account_type_tostring(int type);


/** @brief return a user input integer
 * 
 * ask_for_input: Print a message, then ask the user to input an integer. 
 * If bound is enabled, the function will ask the user to input again if the input integer is out of range.
 * @param[in] _to_print char*: the pointer to a string to be displayed as an instruction of user input.
 * @param[in] bound_enable bool: true: enable lower bound and upper bound. false: disable both bounds.
 * @param[in] lower_bound int: the lower bound of the integer
 * @param[in] upper_bound int: the upper bound of the integer
 * @return int: the user's input value.
 */
int ask_for_input(char* _to_print, bool bound_enable, int lower_bound, int upper_bound);


/** @brief display a string to ask the user to input a string.
 * 
 * string_input: display a string to ask the user to input a string.
 * @param[in] output char* the pointer to the string.
 * @param[in] max_length int: the maximum length of the string. (Memory allocated)
 * @return the string input by user.
 */
char* string_input(char* output, int max_length);


/** @brief create password based on user input
 * 
 * password_create
 * create password based on user input (Linux only)
 * @param [in] output char*: the string to be printed on stdout, asking the user to input password.
 * @param [in] max_length int: the maximum length of the password.
 * @return char*: the pointer to the password string.
 */
char* password_create (char* output, int max_length);

#endif