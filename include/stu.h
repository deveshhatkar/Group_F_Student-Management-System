#pragma once
#ifndef STU_H
#define STU_H

#define STUDENT_NAME_MAXLEN 20
#define COURSE_NUM_PER_STUDENT 3

typedef struct course {
	int course_id;
	double course_score;
}course_t, * p_course_t;

typedef struct student {
	int stu_id;
	char stu_name[STUDENT_NAME_MAXLEN + 1];
	course_t course[COURSE_NUM_PER_STUDENT];
	struct student* next;
}stu_t, * p_stu_t;


void stuinfo_query(p_stu_t, int);

void stu_query_by_name(p_stu_t);

void stu_query_listall(p_stu_t);

void stu_query_id(p_stu_t);

void stuinfo_add(p_stu_t*, char*);

void stuinfo_update(p_stu_t*, char*);

void stuinfo_del(p_stu_t*, char*);


#endif