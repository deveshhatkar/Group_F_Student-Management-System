/** @file utils.c
 * 
 * \brief Internal functions as Utilities
 * 
 * utils.c
 * User functions of the program
 * Includes all the functions defined as user part in the plan.
 * First version completed by Siyuan Chen in Dec.17, 2020 For the second release of the project.
 * 
 * Function comments in header file.
 * 
 * @author Siyuan Chen
 */

#include "utils.h"

char* account_type_tostring(int type){
	switch(type){
		case _type_account_admin:    return "Admin";  break;
		case _type_account_student:  return "Student";break;
		default: return "Unknown";break;
	}
	return "Unknown";
}

int ask_for_input(char* _to_print, bool bound_enable, int lower_bound, int upper_bound){

	/* Self-Check without using assertion */
	if(!(bound_enable == true || bound_enable == false)) { 
			fprintf(stderr,"Internal Error: ask_for_input: bound_enable is %d, not true or false\nProgram Exits\n",bound_enable);
			exit(-1);
	}
	if(upper_bound < lower_bound){
		fprintf(stderr,"Internal Error: ask_for_input: upper bound %d is less then lower bound %d\nProgram Exits\n",upper_bound,lower_bound);
		exit(-1);
	}

	/* Logic: ask_for_input */
	int _to_return;
	for(_to_return=INT_MIN;;){
		if (bound_enable==false)       printf("%s:",_to_print);
		else printf("%s (%d-%d):",_to_print,lower_bound,upper_bound);
		scanf("%d",&_to_return);
		getchar();
		if(bound_enable==1){
			if(_to_return < lower_bound) printf("input %d is lower than limit %d\nPress Enter to try again\n",_to_return,lower_bound);
			else if (_to_return > upper_bound) printf("input %d is higher than limit %d\nPress Enter to try again\n",_to_return,upper_bound);
			else return _to_return;
		}
		getchar();
	}
	fprintf(stderr,"Internal Error: ask_for_input: Exit of infinite loop without return\n");
	exit(-1);
	return INT_MIN;  /* Never return after program exited. */
}

char* string_input(char* output, int max_length){

	// Self-Check
	// length > 0
	if(!(max_length>0)){
		fprintf(stderr,"Internal Error: string_input: max_length is %d, below or equal to 0\nProgram Exits\n",max_length);
		exit(-1);
	}

	char* _to_return = (char*) calloc(max_length + 1, sizeof(char));
	printf("%s: ",output);
	scanf("%s", _to_return);
	getchar();
	return _to_return;
}

char* password_create (char* output, int max_length){
	char _temp_pass[max_length], _temp_pass_2[max_length];
	char* result=(char*)calloc(max_length, sizeof(char));
	for(;;){
		for (int i=0;i<max_length;i++){
			_temp_pass[i]  ='\0';
			_temp_pass_2[i]='\0';
		}
		printf("%s: ",output);
		get_pass(_temp_pass);
		printf("Input Password Again:");
		get_pass(_temp_pass_2);
		if(strcmp(_temp_pass,_temp_pass_2)==0){
			strcpy(result,_temp_pass);
			return result;
		}
		else {
			printf("Password not equal in two inputs.\nInput Again.\n\n");
			continue;
		}
	}
}