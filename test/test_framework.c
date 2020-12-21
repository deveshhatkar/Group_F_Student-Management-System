/** @file test_framework.c
 *  \brief script for testing the functions (Linux only)
 * 
 *  script for testing functions (comparing input and output)
 *  @author Siyuan Chen
 */ 
#include <stdio.h>
#include <stdlib.h>

#define MAX_TEST_CASES 1000
#define MAX_CALL_LENGTH 1000
#define MAX_PATH_LENGTH 1000

int main(){

    FILE *f_in=NULL, *f_result=fopen("../test_result.txt","w+"), *f_comment=NULL;
    char sys_call[MAX_CALL_LENGTH]={0}, path[MAX_PATH_LENGTH]={0};
    char c = '0';
    int failed = 0;

    for(int cases=1; cases<=MAX_TEST_CASES; cases++, failed=0){
        
        // Copy comments
        for(int i=0;i<MAX_PATH_LENGTH;i++){
            path[i] = '\0';
        }
        sprintf(path,"../Tests/%d/comment.txt",cases);
        f_in=fopen(path,"r");
        if(f_in==NULL){
            fprintf(stderr,"Test ended at %d (FILE NOT FOUND)\nProgram Exits\n",cases);
            return 0;
        }
        
        fprintf(f_result,"Test #%d started:  ",cases);
        for(;fscanf(f_in,"%c",&c)!=EOF;){
            fprintf(f_result,"%c",c);
        }
        fprintf(f_result,"\n");
        fclose(f_in);

        
        /* Copy file*/
        system("rm ../bin/input.txt");
        system("rm ../bin/output.txt");
        system("rm ../bin/error.txt");   

        for(int i=0;i<MAX_CALL_LENGTH;i++){
            sys_call[i] = '\0';
        }
        sprintf(sys_call,"cp -a ../Tests/%d/input.txt ../bin/input.txt",cases);
        system(sys_call);
        

        /* Run test */
        system("./stumgr");


        /* Compare Results */

        for(int i=0;i<MAX_CALL_LENGTH;i++){
            sys_call[i] = '\0';
        }
        sprintf(sys_call,"diff ../Tests/%d/output.txt output.txt > ../Tests/%d/Compare_result_%d.txt",cases,cases,cases);
        system(sys_call);

        for(int i=0;i<MAX_CALL_LENGTH;i++){
            sys_call[i] = '\0';
        }
        sprintf(sys_call,"cat error.txt > ../Tests/%d/Compare_result_%d.txt",cases,cases);
        system(sys_call);

        for(int i=0;i<MAX_CALL_LENGTH;i++){
            sys_call[i] = '\0';
        }
        sprintf(sys_call,"../Tests/%d/Compare_result_%d.txt",cases,cases);
        f_in=fopen(sys_call,"r");
        if(f_in==NULL){
            printf("Internal failure: unable to open %s \n",sys_call);
            exit(-1);
        }
        if(fscanf(f_in,"%c",&c)!=EOF){
            fprintf(f_result,"Failed. See %s.\n",sys_call);
        }
        else{
            fprintf(f_result,"Success\n");
        }
        fprintf(f_result,"\n\n");
    }    
    fclose(f_result);
    return 0;
}