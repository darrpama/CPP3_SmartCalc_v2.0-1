#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H

#include "arithmetic.h"

#include <math.h>

#include <stack>
#include <list>

namespace s21 {
class CalculationModel
{
  private:
    std::stack<token> polish_stack;
    std::list<token> list;
    double answer{};

  public:
    CalculationModel() : answer(0){};
    double add(double a, double b);
    double sub(double a, double b);
    double mult(double a, double b);
    double div(double a, double b);
    double mod(double a, double b);
    double degr(double a, double b);

    double sin(double a, double b);
    double cos(double a, double b);
    double tan(double a, double b);
    double asin(double a, double b);
    double acos(double a, double b);
    double atan(double a, double b);

    double log(double a);
    double ln(double a);

    double sqrt(double a);

    void reset();
    double getData();
};

}  // namespace s21 

#endif
