/** @file db.h
 * 
 * \brief Declaration of functions that handle the system initialization and file input/output to make the changes in the system permenant.
 * 
 * db.h
 * Declaration of system initialization and file input/output functions of the program.
 * Includes all the functions that handle making changes performed by the system on Student and User records permanant.
 * Includes Function to initialize the System (at start) with saved data.
 * 
 */

#pragma once
#ifndef DB_H
#define DB_H

#include "stu.h"
#include "user.h"


/** \brief Start application. 
 * 
 * app_start
 * Reads file paths for Student and User records file from configuration file.
 * Promts User sign in and routes the flow based on type of user authenticated.
 * @param[in] conf_file_path: Must hold path to the configuration file.
 * @returns void
 */ 
int app_start(char* conf_file_path);


/** \brief Loads Student and User records from File. 
 * 
 * init_env
 * Reads saved Student records from File generating list of records and attaches it to the 'stu_list' parameter.
 * Reads saved User records from File generating list of records and attaches it to the 'user_list' parameter.
 * @param[out] stu_list: Head of the list of student records retrived by the function.
 * @param[out] user_list: Head of the list of user records retrived by the function.
 * @returns void
 */ 
void init_env(p_stu_t* stu_list, p_user_t* user_list);

/** \brief Saves Student records to File 
 * 
 * istudb_update
 * Saves the records held by 'stu_list' into the file specified by 'str'.
 * @param[in] stu_list: Head of the list of student records maintained by the system.
 * @param[in] str: Holds file path to which records held by 'stu_list' must be saved.
 * @returns void
 */ 
void studb_update(p_stu_t* stu_list, char* str);


/** \brief Saves User records to File 
 * 
 * userdb_update
 * Saves the records held by 'stu_list' into the file specified by 'str'.
 * @param[in] user_list: Head of the list of User records maintained by the system.
 * @param[in] str: Holds file path to which records held by 'user_list' must be saved.
 * @returns void
 */ 
void userdb_update(p_user_t user_list, char* str);

#endif // !DB_H
