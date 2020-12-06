#include "user.h"

void stu_query_id(p_stu_t stu_list)
{
	p_stu_t p = stu_list->next;
	int id, i;
	int flag = 0;
	system("cls");
	printf("Enter ID:");
	scanf("%d", &id);
	while (p != NULL)
	{
		if (p->stu_id == id)
		{
			printf("%4d  %-8s", p->stu_id, p->stu_name);
			for (i = 0; i < COURSE_NUM_PER_STUDENT; i++)
			{
				printf("%5d  %-7.2f", p->course[i].course_id, p->course[i].course_score);
			}
			printf("\n");
			flag = 1;
			break;
		}
		else
		{
			p = p->next;
		}
	}
	if (0 == flag)
	{
		printf("No results!");
	}
	printf("\nEnter any key back to last page.\n");
	CLEAR_BUF;
	_getch();
}

void stu_query_by_name(p_stu_t stu_list)
{
	p_stu_t p = stu_list->next;
	int i;
	char name[USER_NAME_MAXLEN + 1];
	int flag = 0;
	system("cls");
	printf("Enter name:");
	scanf("%s", name);
	while (NULL != p)
	{
		if (strcmp(p->stu_name, name) == 0)
		{
			printf("%04d  %-8s ", p->stu_id, p->stu_name);
			for (i = 0; i < COURSE_NUM_PER_STUDENT; i++)
			{
				printf("%05d %-8.2f", p->course[i].course_id, p->course[i].course_score);
			}
			printf("\n");
			flag = 1;
			break;
		}
		else
		{
			p = p->next;
		}
	}
	if (0 == flag)
	{
		printf("No results");
	}
	printf("\nEnter any key to return\n");
	CLEAR_BUF;
	_getch();
}

void stu_query_listall(p_stu_t stu_list)
{
	p_stu_t p = stu_list->next;
	int i;
	system("cls");
	while (NULL != p)
	{
		printf("%4d  %-8s ", p->stu_id, p->stu_name);
		for (i = 0; i < COURSE_NUM_PER_STUDENT; i++)
		{
			printf("%5d %-8.2f", p->course[i].course_id, p->course[i].course_score);
		}
		printf("\n");
		p = p->next;
	}
	printf("\nEnter any key to return\n");
	CLEAR_BUF;
	_getch();
}

