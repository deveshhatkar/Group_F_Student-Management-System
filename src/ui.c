#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "ui.h"
#include "user.h"
#include "stu.h"

void ui_init()
{
	printf("welcome to Student Record Management System!");
	printf("\nChoose your account type:\n\n");
	printf("[0] Admin\n");
	printf("[1] Student\n");
	printf("[2] Exit\n\n");
}

void get_pass(char* password)
{
	return;
}

void route_admin(p_user_t* user_list, p_stu_t* stu_list, char* str1, char* str2)
{
	return;
}

void route_guest(p_stu_t stu_list) 
{
	return;
}

void ui_admin()
{
	return;
}

void ui_guest()
{
	return;
}

void ui_stu_query(int limit)
{
	return;
}

void ui_user_query()
{
	return;
}

void ui_exit()
{
	return;
}