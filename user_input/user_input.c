/**
 * \file user_input.c
 * \author ade
 * \brief This code will retrieve input from user and assign its value to internal structure variable
 *	Created on: Oct 11, 2017
 *	This code intended for common use.
 *	It only receive data variable that is registered into var_name
 *	Value validation is suppose to be provided outside this program module, only variable name check exist
 *
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "user_input_var_def.h"
#include "user_input.h"


varinput_t var_input[NUMBER_OF_VAR];
static int mapped_input = 0;
static int init_done = 0;
//static int input_set = 0;

void show_registered_var_name(void){
	printf("registered variable name: \n");
	int j;
	for(j=0;j<mapped_input;j++){
		printf("[%d] %s\n",j,var_input[j].Name);
	}
}
void var_name_init(void){
	int i;
	printf("initializaing variable..\n");
	//printf("maximum allowed nuber of input : %d\n", NUMBER_OF_VAR);
	for(i = 0;i<NUMBER_OF_VAR;i++){
		int ret = strcmp(var_name[i],unused);
		if(ret != 0){
			strcpy(var_input[i].Name,var_name[i]);
			mapped_input++;
		}else{
			break;
		}
	}
	init_done = 1;
	show_registered_var_name();
}

int input_check(const char* data, const int f_val){
	int i;
	//check val

	for(i=0;i<mapped_input;i++){
		int ret = strcmp(data,var_input[i].Name);
		if(ret==0){
			//found!
			if(f_val<0 || f_val > 1){
				printf("invalid value, input value '1' or '0' \n");
				printf("value is set to '0'\n");
				var_input[i].value = 0;
			}else{
				var_input[i].value = f_val;
			}

			//input_set ++;
			return 1;
		}
	}
	return 0;
}
int get_input(void){
	char str[50];
	char inp_str[10] = {'\0'};
	int val;
	if(!init_done){
		var_name_init();
	}
	printf("usage: <var name> <space> <value>\n");
	printf("input: ");


	int loc_space = 0;
	fgets(str,50,stdin);
	printf("%d\n",strlen(str));
	char * p = (char*)memchr(str,' ',strlen(str));
	loc_space = p-str;
	if(p!=NULL){
		printf("Found at %d\n", loc_space);
	}
	memcpy(inp_str,str,(p-str));
	val = str[loc_space+1] - '0';
	//printf("inp_str:%s\n",inp_str);
	//printf("val:%d\n",val);
	if(input_check(inp_str,val)){
		printf("var input <%s> registered, continue processing\n",inp_str);
	}else{
		printf("Unregistered input %s \n",str);
	}

	return mapped_input;
}

int get_mapped_input(void)
{
	if(!init_done){
		var_name_init();
	}
	//printf("mapped_input:%d\n",mapped_input);
	return mapped_input;
}
