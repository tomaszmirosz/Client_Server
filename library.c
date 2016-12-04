/*
 * library.c
 *
 *  Created on: 21 lis 2016
 *      Author: tomek
 */

#include "library.h"

#define ERROR 1

int addition(int a, int b) { return a+b; }
int subtraction(int a, int b) { return a-b; }
int multiplication(int a, int b) { return a*b; }
int division(int a, int b) { return a/b; }


char *function(char *input, char *output) {
	int (*ptr_func)(int, int);
	char *args[3];
	char *operation;
	int a, b;
	int len = strlen(input);
	int i, spaces = 0;
	int mark = 0;
	int size = 0;
	int err = 0;

	for(i = 0; i < len; i++) {
		if(input[i] == ' ') {
			size = i - mark;								// długość argumentu
			args[spaces] = malloc(size + 1); 				// bufor na argument
			memcpy(args[spaces], input + mark, size); 		// dodanie danych do bufora
			args[spaces][size] = '\0'; 						// NULL oznaczający koniec stringa
			spaces++; 										// ilość spacji
			mark = i+1; 									// znacznik początku kolejnego argumentu
			if(spaces > 2) break;
		}
	}
	if(spaces != 2) {
		sprintf(output, "ERROR. Write: 'arg1' 'sign' 'arg2'\n");
		err = ERROR;
	}
	if(!err) {

		size = len - mark;
		args[spaces] = malloc(size + 1);
		memcpy(args[spaces], input + mark, size);
		args[spaces][size] = '\0';

		a = atoi(args[0]);
		if(a == 0 && ( args[0][0] != '0' )) {
			sprintf(output, "arg1 is not a number\n");
			err = ERROR;
		}
		b = atoi(args[2]);
		if(b == 0 && ( args[2][0] != '0' )) {
			sprintf(output, "arg2 is not a number\n");
			err = ERROR;
		}
		operation = args[1];
	}
	if(!err) {
		if(strcmp(operation, "+") == 0) {
			ptr_func = &addition;
		} else if(strcmp(operation, "-") == 0) {
			ptr_func = &subtraction;
		} else if(strcmp(operation, "*") == 0) {
			ptr_func = &multiplication;
		} else if(strcmp(operation, "/") == 0) {
			if(b == 0) {
				sprintf(output, "%d %s %d = NaN\n", a, operation, b);
				err = ERROR;
			}
			ptr_func = &division;
		} else {
			sprintf(output, "Invalid operation. Only: '+', '-', '*', '/'\n");
			err = ERROR;
		}
	}

	if(!err) {
		sprintf(output, "%d %s %d = %d\n", a, operation, b, ptr_func(a, b));
	}

	if(spaces > 0) free(args[0]);
	if(spaces > 1) free(args[1]);
	if(spaces > 2) free(args[2]);

	puts(output);

	return output;
}
