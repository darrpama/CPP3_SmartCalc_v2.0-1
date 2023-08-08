/* ************************************************************************** */
/*                                                                            */
/*   s21_calculator                                                           */
/*   By: darrpama <darrpama@student.21-school.ru>                             */
/*                                                                            */
/* ************************************************************************** */

#include "s21_calculator.h"

const Data add = {NAN, add_sub, "+", OK};
const Data sub = {NAN, add_sub, "-", OK};
const Data mul = {NAN, mul_div_mod, "*", OK};
const Data divi = {NAN, mul_div_mod, "/", OK};
const Data mod = {NAN, mul_div_mod, "mod", OK};
const Data degr = {NAN, degree, "^", OK};
const Data clbr = {NAN, bracket, ")", OK};
const Data opbr = {NAN, bracket, "(", OK};
const Data sinu = {NAN, function, "sin", OK};
const Data cosi = {NAN, function, "cos", OK};
const Data tang = {NAN, function, "tan", OK};
const Data loga = {NAN, function, "log", OK};
const Data lna = {NAN, function, "ln", OK};
const Data asinu = {NAN, function, "asin", OK};
const Data acosn = {NAN, function, "acos", OK};
const Data atang = {NAN, function, "atan", OK};
const Data squarert = {NAN, function, "sqrt", OK};
const Data x = {NAN, number_or_x, "x", OK};
const Data zero = {0, number_or_x, "", OK};

Data Begin(char *string) {
  Data danswer = {0};
  Node answer;
  int err = is_correct(string);
  if (err == OK) {
    Node normal_str;
    Node reverced_str;
    Node polish_str;
    Init(&normal_str);
    Init(&reverced_str);
    Init(&polish_str);
    Init(&answer);
    err += Parcer(string, &normal_str);
    Revercer(&normal_str, &reverced_str);
    if (!err) {
      err += PolishParcer(&reverced_str, &polish_str);
      if (!err) {
        Calculator(&polish_str, &answer);
        Destroy(&normal_str);
        Destroy(&reverced_str);
        Destroy(&polish_str);
        danswer = Peek(&answer);
        Destroy(&answer);
      }
    }
  } else {
    danswer.err = ERROR;
  }
  danswer.err = err;
  return danswer;
}

int Parcer(char *string, Node *normal_str) {
  int err = OK;
  for (size_t i = 0; i < strlen(string); i++) {
    char ch = string[i];
    if ((ch >= '0' && ch <= '9') || ch == '.') {
      double number = 0;
      char tmp[255] = {0};
      int k = 0;
      int j = i;
      int flag = 0;
      while ((string[j] >= '0' && string[j] <= '9') || string[j] == '.') {
        if (string[j] == '.') {
          flag++;
          if ((string[j - 1] > '9' || string[j - 1] < '0') ||
              (string[j + 1] > '9' || string[j + 1] < '0')) {
            err = ERROR;
            break;
          }
        }
        tmp[k] = string[j];
        k++;
        j++;
        if (flag > 1 || err) {
          err = ERROR;
          break;
        }
      }
      if (err) {
        break;
      }
      number = atof(tmp);
      Data numberd = {number, number_or_x, "", OK};
      Push(normal_str, numberd);
      i = j - 1;
    } else if (ch == '+') {
      if (!string[i - 1] || string[i - 1] == '(') {
        Push(normal_str, zero);
        Push(normal_str, add);
      } else {
        Push(normal_str, add);
      }
    } else if (ch == '-') {
      if (!string[i - 1] || string[i - 1] == '(') {
        Push(normal_str, zero);
        Push(normal_str, sub);
      } else {
        Push(normal_str, sub);
      }
    } else if (ch == '*') {
      Push(normal_str, mul);
    } else if (ch == '/') {
      Push(normal_str, divi);
    } else if (ch == '^') {
      Push(normal_str, degr);
    } else if (ch == '(') {
      if (string[i + 1] == ')') {
        err = ERROR;
        break;
      }
      Push(normal_str, opbr);
    } else if (ch == ')') {
      Push(normal_str, clbr);
    } else if (string[i] == 'm' && string[i + 1] == 'o' &&
               string[i + 2] == 'd') {
      Push(normal_str, mod);
    } else if (string[i] == 's' && string[i + 1] == 'i' &&
               string[i + 2] == 'n' && string[i - 1] != 'a') {
      Push(normal_str, sinu);
    } else if (string[i] == 'c' && string[i + 1] == 'o' &&
               string[i + 2] == 's' && string[i - 1] != 'a') {
      Push(normal_str, cosi);
    } else if (string[i] == 't' && string[i + 1] == 'a' &&
               string[i + 2] == 'n' && string[i - 1] != 'a') {
      Push(normal_str, tang);
    } else if (string[i] == 'l' && string[i + 1] == 'o' &&
               string[i + 2] == 'g') {
      Push(normal_str, loga);
    } else if (string[i] == 'l' && string[i + 1] == 'n') {
      Push(normal_str, lna);
    } else if (string[i] == 'a' && string[i + 1] == 's' &&
               string[i + 2] == 'i' && string[i + 3] == 'n') {
      Push(normal_str, asinu);
    } else if (string[i] == 'a' && string[i + 1] == 'c' &&
               string[i + 2] == 'o' && string[i + 3] == 's') {
      Push(normal_str, acosn);
    } else if (string[i] == 'a' && string[i + 1] == 't' &&
               string[i + 2] == 'a' && string[i + 3] == 'n') {
      Push(normal_str, atang);
    } else if (string[i] == 's' && string[i + 1] == 'q' &&
               string[i + 2] == 'r' && string[i + 3] == 't') {
      Push(normal_str, squarert);
    } else if (string[i] == 'x' || string[i] == 'X') {
      Push(normal_str, x);
    } else {
      continue;
    }
  }
  return err;
}

int PolishParcer(Node *str, Node *outStr) {
  int err = OK;
  Node s;
  Node *stack = &s;
  Init(stack);
  while (!IsEmpty(str)) {
    Data data = Pop(str);
    if (IsDigit(data)) {
      Push(outStr, data);
    } else if (IsOpenBr(data)) {
      Push(stack, data);
    } else if (IsCloseBr(data)) {
      if (!IsEmpty(stack)) {
        while (!IsOpenBr(Peek(stack))) {
          if (!IsEmpty(stack)) {
            Push(outStr, Pop(stack));
          } else {
            err = ERROR;
            break;
          }
        }
      } else {
        err = ERROR;
        break;
      }
      Pop(stack);
    } else if (IsExpr(data) || IsFunc(data)) {
      while (!IsEmpty(stack)) {
        if (data.priority <= Peek(stack).priority) {
          Push(outStr, Pop(stack));
        } else {
          break;
        }
      }
      Push(stack, data);
    }
  }
  if (!err && !IsEmpty(stack)) {
    if (IsOpenBr(Peek(stack)) || IsCloseBr(Peek(stack))) {
      err = ERROR;
    } else {
      while (!IsEmpty(stack)) {
        Data tmpData = Pop(stack);
        Push(outStr, tmpData);
      }
    }
  }
  Destroy(stack);
  return err;
}

void Calculator(Node *input, Node *output) {
  Node tmp;
  Init(&tmp);
  Revercer(input, &tmp);
  //  print(&tmp);
  while (!IsEmpty(&tmp)) {
    Data data = Pop(&tmp);
    if (IsDigit(data)) {
      Push(output, data);
    } else if (IsExpr(data)) {
      Data op2 = Pop(output);
      Data op1 = Pop(output);
      Data answer = DoOper(op1, op2, data);
      Push(output, answer);
    } else if (IsFunc(data)) {
      Data op = Pop(output);
      Data answer = DoFunc(op, data);
      Push(output, answer);
    }
  }
  Destroy(&tmp);
}

Data DoOper(Data op1, Data op2, Data expr) {
  double answer = 0;
  Data danswer = {0};
  if (IsExpr(expr)) {
    char *oper = expr.oper;
    if (!strcmp(oper, "+")) {
      answer = op1.value + op2.value;
    } else if (!strcmp(oper, "-")) {
      answer = op1.value - op2.value;
    } else if (!strcmp(oper, "*")) {
      answer = op1.value * op2.value;
    } else if (!strcmp(oper, "/")) {
      if (op2.value == 0) {
        danswer.err = ERROR;
      } else {
        answer = op1.value / op2.value;
      }
    } else if (!strcmp(oper, "^")) {
      answer = pow(op1.value, op2.value);
    } else if (!strcmp(oper, "mod")) {
      if (op2.value == 0) {
        danswer.err = ERROR;
      } else {
        answer = fmod(op1.value, op2.value);
      }
    }
  }
  danswer.value = answer;
  return danswer;
}

Data DoFunc(Data op, Data funct) {
  double answer = 0;
  Data danswer = {0};
  if (IsFunc(funct)) {
    char *func = funct.oper;
    if (!strcmp(func, "sin")) {
      answer = sin(op.value);
    } else if (!strcmp(func, "cos")) {
      answer = cos(op.value);
    } else if (!strcmp(func, "tan")) {
      answer = tan(op.value);
    } else if (!strcmp(func, "log")) {
      answer = log(op.value);
    } else if (!strcmp(func, "ln")) {
      answer = log(op.value);
    } else if (!strcmp(func, "asin")) {
      answer = asin(op.value);
    } else if (!strcmp(func, "acos")) {
      answer = acos(op.value);
    } else if (!strcmp(func, "atan")) {
      answer = atan(op.value);
    } else if (!strcmp(func, "sqrt")) {
      answer = sqrt(op.value);
    }
  }
  danswer.value = answer;
  return danswer;
}

int IsDigit(Data data) {
  int res = 0;
  if (!isnan(data.value)) {
    res = 1;
  }
  return res;
}

int IsExpr(Data data) {
  int res = 0;
  if (isnan(data.value)) {
    char *str = data.oper;
    if (!strcmp(str, "+") || !strcmp(str, "-") || !strcmp(str, "*") ||
        !strcmp(str, "/") || !strcmp(str, "^") || !strcmp(str, "mod")) {
      res = 1;
    }
  }
  return res;
}

int IsFunc(Data data) {
  int res = 0;
  if (isnan(data.value)) {
    char *str = data.oper;
    if (!strcmp(str, "sin") || !strcmp(str, "cos") || !strcmp(str, "tan") ||
        !strcmp(str, "log") || !strcmp(str, "ln") || !strcmp(str, "asin") ||
        !strcmp(str, "acos") || !strcmp(str, "atan") || !strcmp(str, "sqrt")) {
      res = 1;
    }
  }
  return res;
}

int IsOpenBr(Data data) {
  int res = 0;
  if (data.oper != NULL) {
    if (!strcmp(data.oper, "(")) {
      res = 1;
    }
  }
  return res;
}

int IsCloseBr(Data data) {
  int res = 0;
  if (!strcmp(data.oper, ")")) {
    res = 1;
  }
  return res;
}

int IsError(Data data) { return data.err; }
