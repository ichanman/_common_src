/*
 * user_input.h
 *
 *  Created on: Oct 11, 2017
 *      Author: ade
 */

#ifndef USER_INPUT_H_
#define USER_INPUT_H_
#include <stdint.h>
//#include "user_input_var_def.h"
extern int get_input(void);

typedef struct{
	char Name[20];
	uint8_t value;
}varinput_t;
#define NUMBER_OF_VAR 5 //input variable use

extern varinput_t var_input[NUMBER_OF_VAR];
extern int get_mapped_input(void);


#endif /* USER_INPUT_H_ */
