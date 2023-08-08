#ifndef IS_CORRECT_H
#define IS_CORRECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_stack.h"

#define FALSE 0
#define TRUE 1
#define EPS 1e-7

int is_correct(char *string);
void filler(char **unary, char **binary);
int null_check(char *str);
int empty_check(char *str);
int num_check(char *str);
int bracket_check(char *str);
int binary_op_check(char *str);
int twise_op_check(char *str);
int foo_check(char *str);
int plus_minus_check(char *str);

int is_digit_or_pm(char ch);
int binary_left(char ch);

#endif  // IS_CORRECT_H
