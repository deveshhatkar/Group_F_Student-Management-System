#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "db.h"
#include "stu.h"
#include "ui.h"
#include "user.h"
#include "platform.h"

char student_file_path[1024];
char user_file_path[1024];

int app_start(char* conf_file_path)
{
	// if (strlen(conf_file) > 0) {
	// 	printf("The program will run in memory-based mode. Configurations will be ignored.");
	// }

	char r_str[1024] = "";

    stu_t* stu_list = NULL;
	user_t* user_list = NULL;

	int button;
	user_t user;

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

	init_env(&stu_list, &user_list);
	

    while (1)
	{
		ui_cls();
		ui_init();
		printf("Please enter a number to select your account type: ");
		button = getchar() - '0';
		if (2 == button)
		{
			ui_exit();
			return 0;
		}
		else if (ADMIN == button || GUEST == button)
			user.type = button;
		else
		{
			fflush(stdin);
			printf("Invalid input!\nEnter any key back to last page.");
			getchar();
			continue;
		}
		ui_cls();
		printf("Username:");
		scanf("%s", &user.name);
		printf("Password:");
		fflush(stdin);
		get_pass(user.pass);
		if (user_auth(user_list, user))
		{
			if (user.type == ADMIN)
			{
				route_admin(&user_list, &stu_list, user_file_path, student_file_path);
			}
			else if (user.type == GUEST)
			{
				route_guest(stu_list);
			}
			break;
		}
		else
		{
			printf("\nNo results!\n");
			fflush(stdin);
			printf("Enter c return to login menu. Enter other key to quit system.");
			if (getchar() != 'c')
				break;
			getchar();
		}

	}
}

void init_env(p_stu_t* stu_list, p_user_t* user_list)
{
	FILE* user_file = fopen(user_file_path, "r+");
	FILE* student_file = fopen(student_file_path, "r+");

	user_t* user_head = (p_user_t)calloc(1, sizeof(user_t));
	user_t* puser = NULL, * user_tail = user_head, tmp_user;

	stu_t* stu_head = (p_stu_t)calloc(1, sizeof(stu_t));
	stu_t* pstu = NULL, * stu_tail = stu_head, * pre = NULL, * pcur = NULL, tmp_stu;
	stu_t* pvisit = NULL;

	int i;

	*user_list = user_head;
	*stu_list = stu_head;

	memset(&tmp_user, 0, sizeof(user_t));
	memset(&tmp_stu, 0, sizeof(stu_t));

	if (user_file != NULL)
	{
		while ((fscanf(user_file, "%s%s%d", &tmp_user.name, &tmp_user.pass, &tmp_user.type)) != EOF)
		{
			puser = (p_user_t)calloc(1, sizeof(user_t));
			strcpy(puser->name, tmp_user.name);
			strcpy(puser->pass, tmp_user.pass);
			puser->type = tmp_user.type;
			if (NULL == user_head->next)
			{
				puser->next = user_head->next;
				user_head->next = puser;
				user_tail = puser;
			}
			else
			{
				user_tail->next = puser;
				user_tail = puser;
			}
		}
		fclose(user_file);
	}
	else
	{
		printf("User data could not be Loaded. Please check if the User data file exists!\n");
	}

	if (student_file != NULL)
	{
		while ((fscanf(student_file, "%d%s", &tmp_stu.stu_id, &tmp_stu.stu_name)) != EOF)
		{
			pstu = (p_stu_t)calloc(1, sizeof(stu_t));
			pstu->stu_id = tmp_stu.stu_id;
			strcpy(pstu->stu_name, tmp_stu.stu_name);
			for (i = 0; i < COURSE_NUM_PER_STUDENT; i++)
			{
				fscanf(student_file, "%d%lf", &pstu->course[i].course_id, &pstu->course[i].course_score);
			}
			if (NULL == stu_head->next)
			{
				pstu->next = stu_head->next;
				stu_head->next = pstu;
				stu_tail = pstu;
			}
			else
			{
				pre = stu_head;
				pcur = stu_head->next;
				while (NULL != pcur)
				{
					if (pcur->stu_id > pstu->stu_id)
					{
						pstu->next = pcur;
						pre->next = pstu;
						break;
					}
					else
					{
						pcur = pcur->next;
						pre = pre->next;
					}
				}
				if (NULL == pcur)
				{
					stu_tail->next = pstu;
					stu_tail = pstu;
				}
			}
		}
		fclose(student_file);
	}
	else
		printf("Student data could not be Loaded. Please check if the Student data file exists!\n");
}

void studb_update(p_stu_t* stu_list, char* str)
{
	FILE* student_file = fopen(student_file_path, "w");
    p_stu_t p = (*stu_list)->next;


    if(NULL == student_file)
        printf("\nStudent File path inside Configuration file incorrect!\nStudent Details could not be updated to File.\n");
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

void userdb_update(p_user_t* user_list, char* str)
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