#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_MAX_SIZE 100
#define STACK_OVERFLOW 100
#define STACK_UNDERFLOW 101

typedef struct Data Data;
typedef struct Node Node;

struct Data {
  double value;
  int priority;
  char *oper;
  int err;
};

struct Node {
  Data *data;  //  данные
  unsigned int n;  //  сколько элементов хранится в стеке
  size_t size;  //  для скольки элементов выделена память
};

enum priority {
  bracket,
  number_or_x,
  add_sub,
  mul_div_mod,
  function,
  degree,
  unaric_minus
};

enum err { OK, ERROR };

void Init(Node *stack);
void Destroy(Node *stack);
void Push(Node *pstack, Data data);
Data Pop(Node *pstack);
Data Peek(Node *pstack);
int IsEmpty(Node *stack);
int IsFull(Node *stack);
void Print(Node *stack);
void Revercer(Node *stack, Node *revercedStack);
#endif  //  S21_STACK_H_
