/** @file user.c
 * 
 * @brief Functions featuring System Initialization and Save Change to Files
 * 
 * user.c
 * Includes all the functions that initialize the system, Load data from files.
 * Includes all the functions defined to make the changes performed by system non-volatile.
 * Includes all the functions that handle file read/write to make changes permenant.
 * 
 * @author Devesh Hatkar
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "db.h"
#include "stu.h"
#include "ui.h"
#include "user.h"

char student_file_path[1024];
char user_file_path[1024];

void app_start(char* conf_file_path)
{
	char r_str[1024] = "";

    stu_t* stu_list = NULL;
	user_t* user_list = NULL;

	int button;
	user_t user;

	FILE* config_file = fopen(conf_file_path, "r");

	if(NULL == config_file)
	{
        printf("Configuration File \"%s\" Not Found!\nProgram Exits\n",conf_file_path);
		getchar(); 
		return -1;
	}
    else
    {
        /* Get file path for saved Student and User records from configuration file */
        fgets(r_str, sizeof(r_str) - 1, config_file);
        strncpy(user_file_path, r_str, strlen(r_str) - 1);

        memset(r_str, 0, sizeof(r_str));

        fgets(r_str, sizeof(r_str) - 1, config_file);
        if (r_str[strlen(r_str)] == '\n')
            strncpy(student_file_path, r_str, strlen(r_str) - 1);
        else
            strncpy(student_file_path, r_str, strlen(r_str));

        int i = 0;
        while(1){
            if(student_file_path[i] == '\r' || student_file_path[i] == '\n'){
                student_file_path[i] = '\0';
                break;
            }
            i++;
        }
		for(i = 0; i<strlen(user_file_path); i++){
			if(user_file_path[i] == '\r' || user_file_path[i] == '\n'){
				user_file_path[i]='\0';
				break;
			}
		}
    }

    /* Load Data from Student and User files to the system and attach to 'stu_list' and 'user_list' heads */
	init_env(&stu_list, &user_list);	

    while (1)
	{
		ui_cls();
		ui_init();

		/* Interface to select User Role */
		printf("Please enter a number to select your account type: ");
		button = getchar() - '0';
		if (2 == button){
			ui_exit();
			return 0;
		}
		else if (ADMIN == button || GUEST == button){
			user.type = button;
		}
		else{
			fflush(stdin);
			printf("Invalid input!\nPress Enter to back to last page.");
			getchar();
			continue;
		}
		ui_cls();

		/* Ask for user name and password */
		printf("Username:");
		scanf("%s", &user.name);
		getchar();
		printf("Password:");
		get_pass(user.pass);
		if (user_auth(user_list, user)){
			if (user.type == ADMIN){
				route_admin(&user_list, &stu_list, user_file_path, student_file_path);
			}
			else if (user.type == GUEST){
				route_guest(stu_list);
			}
			break;
		}
		else{
			printf("\nIncorrect user name, password or account type\n");
			printf("Enter c return to login menu. Enter other key to quit system.\n");
			if (getchar() != 'c')
				break;
			fflush(stdin);
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

	/* Attaching generated linked list to function parameter as output */
	*user_list = user_head;
	*stu_list = stu_head;

	memset(&tmp_user, 0, sizeof(user_t));
	memset(&tmp_stu, 0, sizeof(stu_t));

	if (user_file != NULL)
	{
		/* Retrive User records saved in File as linked list */
		while ((fscanf(user_file, "%s%s%d", &tmp_user.name, &tmp_user.pass, &tmp_user.type)) != EOF)
		{
			puser = (p_user_t)calloc(1, sizeof(user_t));
			strcpy(puser->name, tmp_user.name);
			strcpy(puser->pass, tmp_user.pass);
			puser->type = tmp_user.type;
			if (NULL == user_head->next)
			{
				/* When List initially empty */
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
		printf("User data could not be Loaded.(\"%s\")\nPlease check if the User data file exists!\nPress Enter to exit program\n", user_file_path);
		getchar();
		exit(-1);
	}

	if (student_file != NULL)
	{
		/* Retrive Student Records from file as linked list */
		while ((fscanf(student_file, "%d%s", &tmp_stu.stu_id, &tmp_stu.stu_name)) != EOF)
		{
			pstu = (p_stu_t)calloc(1, sizeof(stu_t));
			pstu->stu_id = tmp_stu.stu_id;
			strcpy(pstu->stu_name, tmp_stu.stu_name);
			for (i = 0; i < COURSE_NUM_PER_STUDENT; i++)
			{
				/* Retriving Courses */
				fscanf(student_file, "%d%lf", &pstu->course[i].course_id, &pstu->course[i].course_score);
			}

			/* Creating linked list based on read records */
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
	{
		printf("Student data could not be Loaded.(\"%s\")\nPlease check if the Student data file exists!\nPress Enter to exit program\n",student_file_path);
		getchar();
		exit(-1);
	}
		
}

void studb_update(p_stu_t* stu_list, char* str)
{
	FILE* student_file = fopen(student_file_path, "w");
    p_stu_t p = (*stu_list)->next;


    if(NULL == student_file)
        printf("\nStudent File path inside Configuration file incorrect!\nStudent Details could not be updated to File.\n");
    else
    {
    	/* Writing records held by 'stu_list' to file */
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
		printf("Student File Updated!\n");
    }
}

void userdb_update(p_user_t user_list, char* str)
{
	FILE* user_file = fopen(user_file_path, "w");
    p_user_t p = user_list->next;
	
	if(NULL == user_file)
    {
        printf("\nUser File path inside Configuration file incorrect!\nUser Details could not be updated to File.\n");
    }
	else
	{
		/* Writing records held by 'user_list' to file */
	    while (NULL != p)
		{
			fprintf(user_file, "%-15s %-10s %d\n", p->name, p->pass, p->type);
			p = p->next;
		}
		fclose(user_file);
		printf("User File Updated!\n");
	}
}