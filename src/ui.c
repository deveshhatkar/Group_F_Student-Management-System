#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ui.h"
#include "user.h"
#include "stu.h"
//#include "platform.h"
#include "utils.h"


#ifdef _WIN32
#include <conio.h>
#elif __linux__
#include <unistd.h>
#elif __APPLE__
#include <unistd.h>
#endif


#define UI_INPUT_BUFFER_LEN 65536
static char ui_input_buffer[UI_INPUT_BUFFER_LEN];
/**
*This function gets the password the user inputs. 
*/
void get_pass(char* password)
{
	int index = 0;
	char ch;
	#ifdef _WIN32
	while ((ch = _getch()) != '\r'){
		if (ch != '\b')
		{
			printf("*");
			password[index++] = ch;
		}
		else
		{
			printf("\b \b");
			index--;
		}
		password[index] = '\0';
	}
	#elif __linux__ || __APPLE__
	char *pass_string = getpass("");
	strncpy(password,pass_string,USER_PASS_MAXLEN);
	password[USER_PASS_MAXLEN - 1] = '\0';
	#endif
}

/**
*this function is used to clear screen in different system.
*/
void ui_cls()
{
	#ifdef _WIN32
	system("cls");  
	printf("win32");
	#elif __linux__
	system("clear");
	#elif __APPLE__
	system("clear");
	#else
	#error "Unknown compiler"
	#endif
}

/**

*/
void ui_pause()
{
	printf("Press Enter to continue...");
	fflush(stdin);
	gets(ui_input_buffer);
}

void ui_invalid_prompt()
{
	printf("Invalid input! Press ENTER to continue.\n");
	gets(ui_input_buffer);
}

char ui_get_option()
{
	for (;;) {
		gets(ui_input_buffer);
		if (strlen(ui_input_buffer) == 1) {
			return ui_input_buffer[0];
		}
		getchar();
	}
}

void ui_init()
{
	printf("welcome to Student Record Management System!");
	printf("\nChoose your account type:\n\n");
	printf("[0] Admin\n");
	printf("[1] Student\n");
	printf("[2] Exit\n\n");
}


void route_admin(p_user_t* user_list, p_stu_t* stu_list, char* str1, char* str2)
{
	char button;
	while (1) {
		ui_cls();
		ui_admin();
		printf("Please enter a number:");
		button = ui_get_option();
		switch (button) {
		case '1':stuinfo_add(stu_list, str2); break;
		case '2':stuinfo_del(stu_list, str2); break;
		case '3':stuinfo_update(stu_list, str2); break;
		case '4':stuinfo_query(*stu_list, ADMIN);   break;
		case '5':user_add(*user_list, str1); break;
		case '6':user_del(*user_list, str1); break;
		case '7':user_update(*user_list, str1); break;
		case '8':ui_user_query(*user_list); break;
		case '9':ui_exit(); break;
		default: ui_invalid_prompt();
		}
	}
}

void route_guest(p_stu_t stu_list)
{
	char button;
	while (1)
	{
		ui_cls();
		ui_guest();
		printf("Please enter a number:");
		button = ui_get_option();
		switch (button){
		case '1':stuinfo_query(stu_list, GUEST); break;
		case '2':ui_exit(); break;
		default: ui_invalid_prompt();
		}
	}
}

void ui_admin()
{
	printf("[1] %-8s new student record\n", "add");
	printf("[2] %-8s existed student record\n", "delete");
	printf("[3] %-8s existed student record\n", "modify");
	printf("[4] %-8s student record\n", "search");
	printf("[5] %-8s new user account record\n", "add");
	printf("[6] %-8s existed account record\n", "delete");
	printf("[7] %-8s existed account record\n", "modify");
	printf("[8] %-8s account record\n", "search");
	printf("[9] exit\n\n");
}

void ui_guest()
{
	printf("[1] %-8s student record\n", "search");
	printf("[2] exit\n");
}

void ui_stu_query(int limit)
{
	ui_cls();
	if (limit == ADMIN){
		printf("[0] Print all student record\n");
	}
	printf("[1] Search student record by ID\n");
	printf("[2] Search student record by name\n");
	printf("[3] Back\n\n");

}

void ui_user_query(p_user_t user_list)
{
	ui_cls();

	char output_string[]="[0] Print all account record\n"
					    "[1] search user account record by user type\n"
					    "[2] search user account record by user name\n"
					    "[3] Back\n\n";

	switch(ask_for_input(output_string,1,0,3)){
		case 0: user_query_listall (user_list);break;
		case 1: user_query_by_level(user_list);break;
		case 2: ui_user_query_by_name (user_list);break;
		default: fprintf(stderr,"Internal Error: ui_user_query: Out of boundary\nProgram Exits\n");exit(-1);
	}

	return;
}

void ui_user_query_by_name (p_user_t user_list)
{
	ui_cls();
	user_query_by_name(user_list, string_input("Enter name", USER_NAME_MAXLEN),1);
	ui_pause();
}

void ui_exit()
{
	ui_cls();
	printf("Thank you for using student record management system!\n");
	ui_pause();
	exit(0);
}

