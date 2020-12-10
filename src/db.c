#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "db.h"
#include "stu.h"
#include "ui.h"
#include "platform.h"

int app_start(char* conf_file)
{
	if (strlen(conf_file) > 0) {
		printf("The program will run in memory-based mode. Configurations will be ignored.");
	}

	stu_t* stu_list = NULL;

	init_env(&stu_list);
	while (1) {
		system(CLS_COMMAND);
		ui_init();
		printf("Please enter a number to proceed: ");
		int button = ui_get_option();
		if (button == '1') {
			ui_exit();
			return 0;
		}
		else if (button == '0') {
			route_admin(&stu_list);
		}
		else {
			ui_invalid_prompt();
			continue;
		}
	}
	return 0;
}

void init_env(p_stu_t* stu_list)
{
	stu_t* stu_head = (p_stu_t)calloc(1, sizeof(stu_t));
	stu_t* pstu = NULL, * stu_tail = stu_head, * pre = NULL, * pcur = NULL, tmp_stu;
	stu_t* pvisit = NULL;
	int i;
	*stu_list = stu_head;
	memset(&tmp_stu, 0, sizeof(stu_t));
}