#include "validator.h"

namespace s21 {

Validator::Validator() {}

int Validator::IsCorrect(const string_type inputString) {
  string_type tempString = inputString;
  bool err = false;
  bool e_check = EmptyCheck(tempString);

  if (e_check == false) {
    bool br_check = BracketCheck(tempString);
    bool n_check = NumCheck(tempString);
    bool pl_min = PlusMinusCheck(tempString);
    bool t_check = TwiseOpCheck(tempString);
    bool f_check = FooCheck(tempString);
    bool b_op_check = BinaryOpCheck(tempString);
    err = br_check || pl_min || n_check || t_check || f_check || b_op_check;
  }
  return err;
}

bool Validator::EmptyCheck(const string_type inputString) {
  bool err = false;
  if (inputString.empty()) {
    err = true;
  }
  return err;
}


int Validator::BracketCheck(const string_type inputString) {
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

int Validator::plus_minus_check(const string_type inputString) {
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

int Validator::num_check(const string_type inputString) {
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

int Validator::twise_op_check(const string_type inputString) {
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

int Validator::binary_op_check(const string_type inputString) {
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

int Validator::foo_check(const string_type inputString) {
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

int Validator::is_digit_or_pm(char ch) {
  int answer = 0;
  if ((ch >= '0' && ch <= '9') || ch == '+' || ch == '-' || ch == 's' ||
      ch == 'c' || ch == 'a' || ch == 't' || ch == 'l' || ch == '(') {
    answer = 1;
  }
  return answer;
}

int Validator::binary_left(char ch) {
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

}  // namespace s21
