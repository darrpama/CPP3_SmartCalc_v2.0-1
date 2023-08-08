#ifndef SRC_S21_CALCULATOR_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_is_correct.h"
#include "s21_stack.h"

Data Begin(char *string);
int Parcer(char *string, Node *normalStr);
int PolishParcer(Node *str, Node *outStr);
void Calculator(Node *input, Node *output);
Data DoOper(Data op1, Data op2, Data expr);
Data DoFunc(Data op, Data funct);

int IsDigit(Data data);
int IsExpr(Data data);
int IsFunc(Data data);
int IsOpenBr(Data data);
int IsCloseBr(Data data);
int IsError(Data data);

#endif  // SRC_S21_CALCULATOR_H_
