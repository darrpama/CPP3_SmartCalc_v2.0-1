/*
This module contains validation functions
 */

#include "s21_is_correct.h"

int is_correct(char *string) {
  char *temp_string = string;
  char **unary = (char **)malloc(sizeof(char *) * 9);
  char **binary = (char **)malloc(sizeof(char *) * 6);
  int err = OK;
  filler(unary, binary);
  int v_check = null_check(temp_string);
  int e_check = empty_check(temp_string);
  err += v_check + e_check;

  if (!null_check(temp_string) && !empty_check(temp_string)) {
    // spaces_deleter(&temp_string);
    int br_check = bracket_check(temp_string);
    int n_check = num_check(temp_string);
    int pl_min = plus_minus_check(temp_string);
    int t_check = twise_op_check(temp_string);
    int f_check = foo_check(temp_string);
    int b_op_check = binary_op_check(temp_string);
    err += br_check + pl_min + n_check + t_check + f_check + b_op_check;
    //    printf("%d, %d, %d, %d, %d\n", br_check, pl_min, n_check, t_check,
    //    f_check);
  }
  free(unary);
  free(binary);
  return err;
}

void filler(char **unary, char **binary) {
  *(unary) = "sin";
  *(unary + 1) = "cos";
  *(unary + 2) = "tan";
  *(unary + 3) = "asin";
  *(unary + 4) = "acos";
  *(unary + 5) = "atan";
  *(unary + 6) = "log";
  *(unary + 7) = "ln";
  *(unary + 8) = "sqrt";
  *(binary) = "*";
  *(binary + 1) = "/";
  *(binary + 2) = "mod";
  *(binary + 3) = "^";
  // '+' and '-' can be unary too
  *(binary + 4) = "+";
  *(binary + 5) = "-";
}

int null_check(char *str) {
  int err = OK;
  if (str == NULL) {
    err = ERROR;
  }
  return err;
}

int empty_check(char *str) {
  int err = OK;
  if (!null_check(str)) {
    if (strlen(str) == 0) {
      err = ERROR;
    }
  } else {
    err = ERROR;
  }
  return err;
}

int bracket_check(char *str) {
  int err = OK;
  for (size_t i = 0; i < strlen(str); i++) {
    const char ch = str[i];
    if (ch == '(') {
      err++;
    }
    if (ch == ')') {
      err--;
    }
  }
  return err;
}

int plus_minus_check(char *str) {
  int err = OK;
  char *ex_str = "1234567890(x.";
  char *ex_str2 = "1234567890()x";
  for (size_t i = 0; i < strlen(str); i++) {
    if (str[i] == '+' || str[i] == '-') {
      if (str[i + 1] == '\0') {
        err = ERROR;
        break;
      } else if (!strchr(ex_str, str[i + 1])) {
        err = ERROR;
        break;
      } else if (i != 0 && !strchr(ex_str2, str[i - 1])) {
        err = ERROR;
        break;
      }
    }
  }
  return err;
}

int num_check(char *str) {
  unsigned int i;
  int err = OK;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == '.' && i != 0) {
      if ((str[i + 1] >= '0' || str[i + 1] <= '9') &&
          (str[i - 1] >= '0' || str[i - 1] <= '9')) {
        continue;
      } else {
        err = ERROR;
        break;
      }
    } else if (str[i] == '.' && i == 0) {
      err = ERROR;
      break;
    } else {
      continue;
    }
  }
  return err;
}

int twise_op_check(char *str) {
  int err = OK;
  for (unsigned int i = 0; i < strlen(str); i++) {
    char ch = str[i];
    char nextch = str[i + 1];
    if (ch == '*' || ch == '/' || ch == '^') {
      if (nextch == ch || nextch == 'm') {
        err = ERROR;
        break;
      }
    } else if (ch == 'm' && nextch == 'o' && str[i + 2] == 'd') {
      if (str[i + 3] != '(' && str[i + 4] == '*' && str[i + 4] == '/' &&
          str[i + 4] == '^') {
        err = ERROR;
        break;
      }
    }
  }
  return err;
}

int binary_op_check(char *str) {
  int err = OK;
  for (unsigned int i = 0; i < strlen(str); i++) {
    char ch = str[i];
    char nextch = str[i + 1];
    if (ch == '*' || ch == '/' || ch == '^') {
      if (i == 0) {
        err = ERROR;
        break;
      }
      char prevch = str[i - 1];
      if (!is_digit_or_pm(nextch) || !binary_left(prevch)) {
        err = ERROR;
        break;
      }
      if (ch == '/' && nextch == '0') {
        err = ERROR;
        break;
      }
    } else if (ch == 'm' && nextch == 'o' && str[i + 2] == 'd') {
      if (i == 0) {
        err = ERROR;
        break;
      }
      char prevch = str[i - 1];
      if (!is_digit_or_pm(str[i + 3]) || !binary_left(prevch)) {
        err = ERROR;
        break;
      }
    }
  }
  return err;
}

int foo_check(char *str) {
  int err = OK;
  for (unsigned int i = 0; i < strlen(str); i++) {
    if (str[i] == 'a' && str[i + 1] == 's' &&
        (str[i + 2] != 'i' || str[i + 3] != 'n' || str[i + 4] != '(' ||
         !is_digit_or_pm(str[i + 5]))) {
      err = ERROR;
      break;
    } else if (str[i] == 'a' && str[i + 1] == 'c' &&
               (str[i + 2] != 'o' || str[i + 3] != 's' || str[i + 4] != '(' ||
                !is_digit_or_pm(str[i + 5]))) {
      err = ERROR;
      break;
    } else if (str[i] == 'a' && str[i + 1] == 't' &&
               (str[i + 2] != 'a' || str[i + 3] != 'n' || str[i + 4] != '(' ||
                !is_digit_or_pm(str[i + 5]))) {
      err = ERROR;
      break;
    } else if (str[i] == 's' && str[i + 1] == 'q' &&
               (str[i + 2] != 'r' || str[i + 3] != 't' || str[i + 4] != '(' ||
                !is_digit_or_pm(str[i + 5]))) {
      err = ERROR;
      break;
    } else if (str[i] == 's' && str[i + 1] == 'i' &&
               (str[i + 2] != 'n' || str[i + 3] != '(' ||
                !is_digit_or_pm(str[i + 4]))) {
      err = ERROR;
      break;
    } else if (str[i] == 'c' &&
               (str[i + 1] != 'o' || str[i + 2] != 's' || str[i + 3] != '(' ||
                !is_digit_or_pm(str[i + 4]))) {
      printf("5");
      err = ERROR;
      break;
    } else if (str[i] == 't' && str[i + 1] == 'a' &&
               (str[i + 2] != 'n' || str[i + 3] != '(' ||
                !is_digit_or_pm(str[i + 4]))) {
      printf("6");
      err = ERROR;
      break;
    } else if (str[i] == 'l' && str[i + 1] == 'o' &&
               (str[i + 2] != 'g' || str[i + 3] != '(' ||
                !is_digit_or_pm(str[i + 4]))) {
      err = ERROR;
      break;
    } else if (str[i] == 'l' && str[i + 1] == 'n' && str[i + 2] != '(' &&
               !is_digit_or_pm(str[i + 3])) {
      err = ERROR;
      break;
    } else {
      continue;
    }
  }
  // printf("%d\n", err);
  return err;
}

int is_digit_or_pm(char ch) {
  int answer = 0;
  if ((ch >= '0' && ch <= '9') || ch == '+' || ch == '-' || ch == 's' ||
      ch == 'c' || ch == 'a' || ch == 't' || ch == 'l' || ch == '(') {
    answer = 1;
  }
  return answer;
}

int binary_left(char ch) {
  int answer = 0;
  if ((ch >= '0' && ch <= '9') || ch == ')') {
    answer = 1;
  }
  return answer;
}

// int binary_right(char ch) {
//   int answer = 0;
//   if ((ch >= '0' && ch <= '9') || ch == '(' || ch == 's' || ch == 'c' || ch
//   == 'a' || ch == 't' || ch == 'l') {
//       ) {
//     answer = 1;
//   }
//   return answer;
// }
