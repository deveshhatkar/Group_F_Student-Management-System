/** @file user.c
 * 
 * @brief User part functions of the program
 * 
 * user.c
 * User functions of the program
 * Includes all the functions defined as user part in the plan.
 * 
 * @author Siyuan Chen
 * 
 */
#include "user.h"

int user_auth(p_user_t user_list, user_t user)
{
	p_user_t now = user_list;
	for(;now!=NULL;now=now->next)
	{
		if((strcmp(now->name,user.name)==0) && 
		   (strcmp(now->pass,user.pass)==0) &&
		   ((now->type==user.type) || (user.type == -1))) return 1;
	}
	// Return 0 if nothing found.
	return 0;
}

/* With UI */
void user_query_by_level(p_user_t user_list, int account_type)
{
	p_user_t p = user_list;
	for(p=p->next;p!=NULL;p=p->next) {
		if(p->type==account_type || account_type == -1) {
			printf("Username: %s, Type: %s\n", p->name,  account_type_tostring(p->type));
		}
	}
	printf("Press Enter to return to the menu...");
	getchar();
	return;
}

int user_query_by_name(p_user_t user_list, char* input, int enable_output) 
{
	if(user_list==NULL){
		if(enable_output){
			printf("Empty user list, nothing to update\nPress Enter to return to the menu...");
			getchar();
		}
		return 0;
	}
	p_user_t p = user_list;
	int count=0;
	for(p=p->next;p!=NULL;p=p->next){
		if(strcmp(input,p->name)==0){
			count++;
			if (enable_output) printf("Username:%s, Type:%s\n",p->name, account_type_tostring(p->type));
		}
	}
	if (enable_output==1 && count==0) printf("No result found\n");
	return count;
}

/* With UI */
void user_add(p_user_t user_list, char* file_to_save) 
{
	p_user_t p = user_list;
	p_user_t _to_add=(p_user_t)calloc(1,sizeof(p_user_t));
	ui_cls();

	// Input
	printf("Input the user information to be added:\n");

	strcpy(_to_add->name, string_input("Username", USER_NAME_MAXLEN));
	if(user_query_by_name(user_list,_to_add->name, 0) != 0){
		printf("Username %s already exists.\nPress any key to return to menu\n",_to_add->name);
		getchar();
		return;
	}
	char* t=password_create("Password",USER_PASS_MAXLEN);
	strcpy(_to_add->pass, t);
	_to_add->type = ask_for_input("Account type (0:Admin, 1:Student)",true,0,1);

	for(;p->next!=NULL;p=p->next); // Navigate to the end of the linked list.
	p->next = _to_add;
	_to_add->next = NULL;

	userdb_update(user_list, file_to_save);
	printf("\nEnter to return...");
	getchar();

	return;
}

/* With UI */
void user_update(p_user_t user_list, char* file_to_save)
{
	if(user_list==NULL){
		printf("Empty user list, nothing to update\nPress Enter to return to the menu...");
		getchar();
		return;
	}
	p_user_t p = user_list;
	char *username_temp, *password_temp;
	int account_type_temp = -1;
	char *user_to_update = string_input("Input Username",USER_NAME_MAXLEN);
	for(p=p->next;p!=NULL;p=p->next){
		if(strcmp(user_to_update,p->name)==0){
			/* Did not implement catching keys from terminal, as it is OS specific */
			username_temp = string_input("Update Username (Enter -1 to skip)",USER_NAME_MAXLEN);
			if(strcmp(username_temp,"-1")!=0) {
				strcpy(p->name,username_temp);
				printf("Username updated\n");
			}
			password_temp = password_create("Update Password (Enter -1 as password to skip)",USER_PASS_MAXLEN);
			if(strcmp(password_temp,"-1")!=0) {
				strcpy(p->pass, password_temp);
				printf("Password updated\n");
			}
			account_type_temp = ask_for_input("Update Account Type(0: Admin, 1:Student, -1:Do not update)",true,-1,1);
			if(account_type_temp != -1) {
				p->type = account_type_temp;
				printf("Account type updated\n");
			}
			userdb_update(user_list,file_to_save);
			printf("\nEnter to return...");
			getchar();
			return;
		}
	}
	printf("User not found\n");
	getchar();
	return;
}

/* With UI */
void user_del(p_user_t user_list, char* file_to_save)
{
	if(user_list==NULL){
		printf("Empty user list, nothing to delete\nPress Enter to return to the menu...");
		getchar();
		return;
	}
	p_user_t p = user_list;
	p_user_t p_next = user_list->next;
	char confimation = 'n';
	char *user_to_delete = string_input("Input Username",USER_NAME_MAXLEN);

	for(;p_next!=NULL;p=p->next, p_next=p_next->next){
		if(strcmp(user_to_delete, p_next->name)==0){
			printf("Confirm delete account %s? (y/n):", p_next->name);
			scanf("%c",&confimation);
			getchar();
			if(confimation == 'y' || confimation == 'Y'){
				p->next=p_next->next;
				free(p_next);
				free(user_to_delete);
				userdb_update(user_list,file_to_save);
				printf("Account deleted\nEnter to return...");
				getchar();
				return;
			}
			else return;
		}
	}
	free(user_to_delete);
	printf("User not found\n");
	getchar();
	return;
}

