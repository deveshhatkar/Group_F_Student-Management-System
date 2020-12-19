// Todo: Doxygen Main Page and comments

// utils.c
// Siyuan Chen 
// Dec.18, 2020

#include "utils.h"

// STUB
char* account_type_tostring(int type){
	switch(type){
		case _type_account_admin:    return "Admin";  break;
		case _type_account_student:  return "Student";break;
		default: return "Unknown";break;
	}
	return "Unknown";
}

// ask_for_input
int ask_for_input(char* _to_print, bool bound_enable, int lower_bound, int upper_bound){

	// Self-Check without using assertion

	// bound_enable: true || false
	if(!(bound_enable == true || bound_enable == false)) { 
			fprintf(stderr,"Internal Error: ask_for_input: bound_enable is %d, not true or false\nProgram Exits\n",bound_enable);
			exit(-1);
	}

	// lower_bound <= upper_bound
	if(upper_bound < lower_bound){
		fprintf(stderr,"Internal Error: ask_for_input: upper bound %d is less then lower bound %d\nProgram Exits\n",upper_bound,lower_bound);
		exit(-1);
	}

	// Logic: ask_for_input
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
	return INT_MIN;  // Never return after program exited.
}

//string_input
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

