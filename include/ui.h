/**
* \file ui.c
* contains the functions which is about to display the system interface.
*
*this file is mainly to display the interface of the option between guest and admin and their relative functions.
*/
#pragma once
#ifndef UI_H
#define UI_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "stu.h"
#include "user.h"

/**
* /brief this function is used to clear screen in different system.
*/
void ui_cls();

/**
* /brief this function is used to pause the interface.
*/
void ui_pause();

/**
* /brief this function is used when the user input the wrong character.
*/
void ui_invalid_prompt();

/**
* /brief this function is used to get the option the user choose. The input should be one character.
*/
char ui_get_option();

/**
* /brief This function gets the password the user inputs.
*/
void get_pass(char*);

/**
* /brief this function is used to invoke different functions based on the character user inputs.
*@param[in] user_list the linked list which concludes user's information
*@param[in] stu_list the linked list which concludes student's information
*@param[in] str1 user file  which is used when we need to update user database.
*@param[in] str2 student file which is used when we need to update student database.
*/
void route_admin(p_user_t*, p_stu_t*, char*, char*);

/**
* /brief this function is used when the user is a guest.it just has one function,which is the stuinfo_query function.
*@param[in] stu_list
*/
void route_guest(p_stu_t);

/**
* /brief this function is used to set a initialization interface.
*/
void ui_init();

/**
* /brief this function displays the admin interface.
*/
void ui_admin();

/**
* /brief this function displays the guest interface.
*/
void ui_guest();

/**
* /brief this function is to display the interface what user could
*do to search their results. for the admin, the interface will display one more
* option, which is to print all students' records.
*/
void ui_stu_query(int);

/**
* /brief this function is to display the interface what user could
*do to get accont records.
*/
void ui_user_query(p_user_t);
/**
* /brief this function is to get account records by name.
*/
void ui_user_query_by_name(p_user_t);

/**
* /brief this function is used to exit the system.
*/
void ui_exit();

#endif
