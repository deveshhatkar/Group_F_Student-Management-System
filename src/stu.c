#include "stu.h"
#include "ui.h"
#include "user.h"

void stuinfo_query(p_stu_t stu_list)
{
	char button;
	while (1)
	{
		ui_stu_query();
		printf("Please enter a number:");
		button = ui_get_option();
		switch (button)
		{
		case '0': stu_query_listall(stu_list); break;
		case '1': stu_query_id(stu_list); break;
		case '2': stu_query_by_name(stu_list); break;
		case '3': return;
		default: ui_invalid_prompt();
		}
	}
}

void stu_query_id(p_stu_t stu_list)
{
	p_stu_t p = stu_list->next;
	int id, i, flag = 0;
	ui_cls();
	printf("Enter ID:");
	scanf("%d", &id);
	while (p) {
		if (p->stu_id == id) {
			printf("%4d  %-8s", p->stu_id, p->stu_name);
			for (i = 0; i < COURSE_NUM_PER_STUDENT; i++) {
				printf("%5d  %-7.2f", p->course[i].course_id, p->course[i].course_score);
			}
			printf("\n");
			flag = 1;
			break;
		}
		else {
			p = p->next;
		}
	}
	if (!flag) {
		printf("No results!");
	}
	printf("\nPress ENTER to last page.\n");
	ui_pause();
}

void stuinfo_add(p_stu_t* stu_list)
{
	p_stu_t p = (p_stu_t)calloc(1, sizeof(stu_t));
	p_stu_t pre = NULL, pcur = NULL;
	int flag, i;
	while (1) {
		flag = 1;
		ui_cls();
		printf("Please enter a student's info to create record.\n");
		printf("The format is [ID Name] and %d course record [CourseId CourseScore]\n", COURSE_NUM_PER_STUDENT);
		scanf("%d%s", &p->stu_id, &p->stu_name);
		for (i = 0; i < COURSE_NUM_PER_STUDENT; i++) {
			scanf("%d%lf", &p->course[i].course_id, &p->course[i].course_score);
		}
		if (!(*stu_list)->next) {
			p->next = (*stu_list)->next;
			(*stu_list)->next = p;
		}
		else {
			pre = (*stu_list);
			pcur = (*stu_list)->next;
			while (NULL != pcur) {
				if (pcur->stu_id > p->stu_id) {
					p->next = pcur;
					pre->next = p;
					break;
				}
				else if (pcur->stu_id == p->stu_id) {
					flag = 0;
					break;
				}
				else {
					pcur = pcur->next;
					pre = pre->next;
				}
			}
			if (!pcur) {
				pre->next = p;
			}
		}
		if (flag) {
			printf("The record has been created into system!\n");
		}
		else {
			printf("Add failed!\nThe ID has been used.\n");
		}
		printf("\nDo you want to add more? [y/n]");
		char c = ui_get_option();
		if (c != 'y')
		{
			break;
		}
	}
}

void stuinfo_del(p_stu_t* stu_list)
{
	p_stu_t pre = *stu_list;
	p_stu_t pcur = (*stu_list)->next;
	int id, flag = 0;
	ui_cls();
	printf("Enter the ID need to be deleted:");
	scanf("%d", &id);
	while (pcur) {
		if (pcur->stu_id == id) {
			pre->next = pcur->next;
			free(pcur);
			pcur = NULL;
			flag = 1;
			break;
		}
		else {
			pcur = pcur->next;
			pre = pre->next;
		}
	}
	if (!flag) {
		printf("No results.\n");
	}
	else {
		printf("The record has been deleted!");
	}
	printf("\nPress ENTER to return.\n");
	ui_pause();
}

void stu_query_by_name(p_stu_t stu_list)
{
	p_stu_t p = stu_list->next;
	int i;
	char name[USER_NAME_MAXLEN + 1];
	int flag = 0;
	ui_cls();
	printf("Enter name:");
	scanf("%s", name);
	while (p) {
		if (!strcmp(p->stu_name, name)) {
			printf("%04d  %-8s ", p->stu_id, p->stu_name);
			for (i = 0; i < COURSE_NUM_PER_STUDENT; i++) {
				printf("%05d %-8.2f", p->course[i].course_id, p->course[i].course_score);
			}
			printf("\n");
			flag = 1;
			break;
		}
		else {
			p = p->next;
		}
	}
	if (!flag) {
		printf("No results");
	}
	printf("\nEnter any key to return\n");
	ui_pause();
}

void stu_query_listall(p_stu_t stu_list)
{
	p_stu_t p = stu_list->next;
	int i;
	ui_cls();
	while (p) {
		printf("%4d  %-8s ", p->stu_id, p->stu_name);
		for (i = 0; i < COURSE_NUM_PER_STUDENT; i++) {
			printf("%5d %-8.2f", p->course[i].course_id, p->course[i].course_score);
		}
		printf("\n");
		p = p->next;
	}
	printf("\nEnter any key to return\n");
	ui_pause();
}

void stuinfo_update(p_stu_t* stu_list)
{
	p_stu_t p = (*stu_list)->next;
	int flag = 0, id, i;
	ui_cls();
	printf("Enter ID:");
	scanf("%d", &id);
	while (p) {
		if (p->stu_id == id)
		{
			printf("Please modify the student's record.\n");
			printf("The format is [ID Name] and %d course record [CourseId CourseScore]\n", COURSE_NUM_PER_STUDENT);
			scanf("%d%s", &p->stu_id, p->stu_name);
			for (i = 0; i < COURSE_NUM_PER_STUDENT; i++) {
				scanf("%d%lf", &p->course[i].course_id, &p->course[i].course_score);
			}
			flag = 1;
			break;
		}
		else {
			p = p->next;
		}
	}
	if (!flag) {
		printf("No results.\n");
	}
	else {
		printf("The record has been modified!");
	}
	printf("\nEnter any key to return\n");
	ui_pause();
}
