#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "db.h"
#include "stu.h"
#include "ui.h"
#include "platform.h"

char student_file_path[1024] = "";
char user_file_path[1024] = "";

int app_start(char* conf_file_path)
{
	// if (strlen(conf_file) > 0) {
	// 	printf("The program will run in memory-based mode. Configurations will be ignored.");
	// }

	stu_t* stu_list = NULL;

	FILE* config_file = fopen(conf_file_path, "r");


	if(NULL == config_file)
        printf("Configuration File Not Found!");
    else
    {
        //Getting User file path from Config file.
        fgets(r_str, sizeof(r_str) - 1, config_file);
        strncpy(user_file_path, r_str, strlen(r_str) - 1);

        memset(r_str, 0, sizeof(r_str));

        fgets(r_str, sizeof(r_str) - 1, config_file);
        if (r_str[strlen(r_str)] == '\n')
            strncpy(student_file_path, r_str, strlen(r_str) - 1);
        else
            strncpy(student_file_path, r_str, strlen(r_str));

        int i = 0;

        while(1)
        {
            if(student_file_path[i] == '\n')
            {
                student_file_path[i] = '\0';
                break;
            }
            i++;
        }

        user_file_path[strlen(user_file_path)] = '\0';
    }

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

void studb_update(p_stu_t* stu_list)
{
	FILE* student_file = fopen(student_file_path, "w");
    p_stu_t p = (*stu_list)->next;


    if(NULL == student_file)
        printf("\nStudent File path inside Configuration file incorrect!\nStudent Details could not be updated to File.");
    else
    {
        while (NULL != p)
		{
			fprintf(student_file, "%4d  %-10s", p->stu_id, p->stu_name);
			for (int i = 0; i < COURSE_NUM_PER_STUDENT; i++)
			{
				fprintf(student_file, "%5d  %-7.2f", p->course[i].course_id, p->course[i].course_score);
			}
			fprintf(student_file, "\n");
			p = p->next;
		}

		fclose(student_file);
		printf("Student File Updated!");
    }
}

void userdb_update(p_user_t* user_list)
{
	FILE* user_file = fopen(user_file_path, "w");
    p_user_t p = (*user_list)->next;
	
	if(NULL == user_file)
    {
        printf("\nUser File path inside Configuration file incorrect!\nUser Details could not be updated to File.");
    }
	else
	{
	    printf("\nFound user file!");
	    while (NULL != p)
		{
			fprintf(user_file, "%-15s %-10s %d\n", p->name, p->pass, p->type);
			p = p->next;
		}

		fclose(user_file);
		printf("User File Updated!");
	}
}