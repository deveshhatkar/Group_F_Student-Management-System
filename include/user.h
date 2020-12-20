/** @file user.h
 * 
 * \brief Declaration of user part functions of the program
 * 
 * user.h
 * Declaration of User functions of the program
 * Includes all the functions defined as user part in the plan.
 * 
 */
#pragma once
#ifndef USER_H
#define USER_H

#define USER_NAME_MAXLEN 20
#define USER_PASS_MAXLEN 16

enum { ADMIN, GUEST };

typedef struct user {
	char name[USER_NAME_MAXLEN + 1];
	char pass[USER_PASS_MAXLEN + 1];
	int type;
	struct user* next;
}user_t, *p_user_t;


/** \brief Check username and password
 * 
 * user_auth: authenticate the user with username and password.
 * @param[in] user_list p_user_t: The head of linked list of all user accounts.
 * @param[in] user user_t: includes name and password being input for authenticate
 * @returns 1 if username and password both match. Return 0 if one of them does not match.
 */ 
int user_auth(p_user_t, user_t);


/** @brief List all users with name and type
 * 
 * user_query_listall
 * Print all users with name and type to stdout.
 * @param[in] user_list p_user_t: The head of linked list of all user accounts.
 */
void user_query_listall(p_user_t);


/** @brief List all users of admin type or student type. 
 * 
 * user_query_by_level
 * Print all users with name of a certain type to stdout.
 * @param[in] user_list p_user_t: The head of linked list of all user accounts.
 * @param[in] 
 */
void user_query_by_level(p_user_t);


/** @brief List all user with the name input
 * 
 * user_query_by_name
 * Print all users with the name input to stdout
 * @param[in] user_list p_user_t: The head of linked list of all user accounts.
 * @param[in] input char*: string of the name input
 * @param[in] enable_output int: 1 to enable output, 0 to disable output. 
 * @return the number of accounts that have the name.
 */ 
int user_query_by_name(p_user_t user_list, char* input, int enable_output);


/** @brief add a user based on user input
 * 
 * user_add
 * add a user based on user input
 * @param[in] user_list p_user_t: The head of linked list of all user accounts.
 * @param[in] file_to_save char*:string of filename to be saved. Will be passed to db part.
 */
void user_add(p_user_t, char*);


/** @brief modify the information of a user based on the name input
 * 
 * user_update
 * modify the information of a user based on the name input by user.
 * If there are multiple users with same name, the function will modify the first one.
 * @param[in] user_list p_user_t: The head of linked list of all user accounts.
 * @param[in] file_to_save char*:string of filename to be saved. Will be passed to db part.
 */
void user_update(p_user_t, char*);


/** @brief delete a user by the name
 * 
 * user_del
 * Delete the user based on the name input by the user.
 * If there are multiple users with same name, the function will delete the first one.
 * @param[in] user_list p_user_t: The head of linked list of all user accounts.
 * @param[in] file_to_save char*:string of filename to be saved. Will be passed to db part.
 */
void user_del(p_user_t, char*);

#endif