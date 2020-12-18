// Todo: Doxygen comments; coding conservasion.
// TO BE FIXED: details of "key" of finding a user in the linked list is ambigious.
// ==> two kind of user search by name is implemented.

// user.c
// Siyuan Chen
// Dec.17, 2020

#include <stdlib.h>
#include "user.h"
#include "ui.h"
#include "utils.h"

int user_auth(p_user_t user_list, user_t user) // **
{
	p_user_t now = user_list;
	for(;now->next!=NULL;now=now->next)
	{
		if((strcmp(now->name,user.name)==0) && 
		   (strcmp(now->pass,user.pass)==0)) return 1;
		//[DEBUG ONLY] else printf("%s:%s=%d ; %s:%s=%d\n",now->name, user.name,strcmp(now->name,user.name) , now->pass, user.pass, strcmp(now->pass,user.pass));
	}
	// Return 0 if nothing found.
	return 0;
}

void user_query_listall(p_user_t user_list)
{
	ui_cls();
	for(p_user_t p=user_list;p->next!=NULL;p=p->next){
		printf("Username: %s, Type of Account: ",p->name);
		if(p->type==_type_account_admin) printf("ADMIN");           // todo: solve enum conflict.
		else if (p->type==_type_account_student) printf("Student");
		else printf("Unknown type %d",p->type);
		printf("\n");
	}
	getchar();
	return;
}

void user_query_by_level(p_user_t user_list)
{
	int account_type = ask_for_input("Enter an account type(0: Admin, 1: Student)", 1, 0, 1);
	p_user_t p = user_list;
	for(;p->next!=NULL;p=p->next) if(p->type==account_type) printf("Username: %s, Type: %s\n", p->name,  account_type_tostring(p->type));
	getchar();
	return;
}

int user_query_by_name(p_user_t user_list, char* input, int enable_output) 
{
	p_user_t p = user_list;
	int count=0;
	printf("char_input=%s\n",input);
	for(;p->next!=NULL;p=p->next){
		if(strcmp(input,p->name)==0){
			count++;
			if (enable_output) printf("Username:%s, Type:%s\n",p->name, account_type_tostring(p->type));
		}
		//[DEBUG ONLY] else printf("%s:%s=%d\n",input,p->name,strcmp(input,p->name));
	}
	if (enable_output==1 && count==0) printf("No result found\n");
	return count;
}


void user_add(p_user_t user_list, char* str1) // with ui
{
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

	// Add to the second node of the linked list (will not change the first item)
	// STUB
	_to_add->next = user_list -> next;
	user_list->next = _to_add;

	//userdb_update(user_list,str1);

	return;
}

void user_update(p_user_t user_list, char* str1)
{
	p_user_t p = user_list;
	char *_temp_username, *_temp_password;
	int _temp_account_type = -1;
	char *_user_to_update = string_input("Input Username",USER_NAME_MAXLEN);
	for(;p->next!=NULL;p=p->next){
		if(strcmp(_user_to_update,p->name)==0){
			_temp_username = string_input("Update Username (Enter -1 to skip)",USER_NAME_MAXLEN);
			if(strcmp(_temp_username,"-1")!=0) {
				strcpy(user_list->name,_temp_username);
				printf("Username updated\n");
			}
			_temp_password = password_create("Update Password (Enter -1 twice to skip)",USER_PASS_MAXLEN);
			if(strcmp(_temp_password,"-1")!=0) {
				strcpy(user_list->pass, _temp_password);
				printf("Password updated\n");
			}
			_temp_account_type = ask_for_input("Update Account Type\n(0: Admin, 1:Student, -1:Do not update)",true,-1,1);
			if(_temp_account_type != -1) {
				user_list->type = _temp_account_type;
				printf("Account type updated\n");
			}
			//userdb_update(user_list,str1);
			return;
		}
	}
	printf("User not found\n");
	getchar();
	return;
}

void user_del(p_user_t user_list, char* str1)
{
	// Todo: 1-element linked list issue
	p_user_t p = user_list;
	p_user_t p_next = user_list->next;
	char confimation = 'n';
	char *user_to_delete = string_input("Input Username",USER_NAME_MAXLEN);
	for(;p_next!=NULL;p_next=p_next->next){
		if(strcmp(user_to_delete, p_next->name)==0){
			printf("Confirm delete account %s? (y/n):", p_next->name);
			scanf("%c",&confimation);
			getchar();
			fflush(stdin);
			if(confimation == 'y' || confimation == 'Y'){
				p->next=p_next->next;
				free(p_next);
				free(user_to_delete);
				printf("Account deleted\n");
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

char* password_create (char* output, int max_length){
	char _temp_pass[max_length], _temp_pass_2[max_length];
	char* result=(char*)calloc(max_length, sizeof(char));
	for(;;){
		for (int i=0;i<max_length;i++){
			_temp_pass[i]  ='\0';
			_temp_pass_2[i]='\0';
		}
		printf("%s: ",output);
		get_pass(_temp_pass);
		printf("Input Password Again:");
		get_pass(_temp_pass_2);
		if(strcmp(_temp_pass,_temp_pass_2)==0){
			strcpy(result,_temp_pass);
			return result;
		}
		else {
			printf("Password not equal in two inputs.\nInput Again.\n\n");
			continue;
		}
	}
}