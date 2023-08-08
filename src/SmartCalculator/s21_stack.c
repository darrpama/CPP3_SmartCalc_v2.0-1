#include "s21_stack.h"

void Init(Node *stack) {
  stack->n = 0;
  stack->size = 0;
  stack->data = NULL;
}

void Destroy(Node *stack) {
  free(stack->data);
  stack->n = 0;
  stack->size = 0;
  stack->data = NULL;
}

void Push(Node *stack, Data data) {
  if (IsFull(stack)) {
    stack->size += 10;
    stack->data = realloc(stack->data, stack->size * sizeof(Data));
  }
  stack->data[stack->n] = data;
  stack->n++;
}

Data Pop(Node *stack) {
  Data res = stack->data[stack->n - 1];
  stack->n--;
  return res;
}

Data Peek(Node *stack) {
  Data res = {NAN, 0, "", OK};
  res.priority = stack->data[stack->n - 1].priority;
  res.value = stack->data[stack->n - 1].value;
  char *tmp = stack->data[stack->n - 1].oper;
  res.oper = tmp;
  return res;
}

int IsEmpty(Node *stack) { return stack->n == 0; }

int IsFull(Node *stack) { return stack->n == stack->size; }

void Print(Node *stack) {
  for (unsigned int i = 0; i < stack->n; i++) {
    Data *tmp = &stack->data[i];
    printf("(%lf %d %s); ", tmp->value, tmp->priority, tmp->oper);
  }
  printf("\n");
}

void Revercer(Node *stack, Node *revercedStack) {
  while (!IsEmpty(stack)) {
    Data tmpData = Pop(stack);
    Push(revercedStack, tmpData);
  }
}