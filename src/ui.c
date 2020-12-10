#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ui.h"
#include "user.h"
#include "stu.h"
#include "platform.h"

#define UI_INPUT_BUFFER_LEN 65536
static char ui_input_buffer[UI_INPUT_BUFFER_LEN];

void get_pass(char* password)
{
	// Todo
}

void ui_cls()
{
	system(CLS_COMMAND);
}

void ui_pause()
{
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
	}
}

void ui_init()
{
	printf("welcome to Student Record Management System!\n");
	printf("[0] Enter System\n");
	printf("[1] Exit\n\n");
}

void route_admin(p_stu_t* stu_list)
{
	char button;
	while (1) {
		ui_cls();
		ui_admin();
		printf("Please enter a number:");
		button = ui_get_option();
		switch (button) {
		case '1':stuinfo_add(stu_list); break;
		case '2':stuinfo_del(stu_list); break;
		case '3':stuinfo_update(stu_list); break;
		case '4':stuinfo_query(*stu_list);   break;
		case '5':ui_exit(); break;
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
	printf("[5] exit\n");
}

void ui_stu_query()
{
	ui_cls();
	printf("[0] Print all student record\n");
	printf("[1] Search student record by ID\n");
	printf("[2] Search student record by name\n");
	printf("[3] Back\n\n");

}

void ui_user_query()
{
	ui_cls();
	printf("[0] Print all account record\n");
	printf("[1] search user account record by user type\n");
	printf("[2] search user account record by user name\n");
	printf("[3] Back\n\n");
}

void ui_exit()
{
	ui_cls();
	printf("Thank you for using student record management system!\n");
	ui_pause();
	exit(0);
}
