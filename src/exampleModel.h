#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H

#include "arithmetic.h"

#include <math.h>

namespace s21 {
class CalculationModel
{
    private:
        std::list<token> stack;

        double answer{};

    public:
        CalculationModel():answer(0){};
        void add(double a, double b);
        void sub(double a, double b);
        void mult(double a, double b);
        void div(double a, double b);
        void mod(double a, double b);
        void degr(double a, double b);

        void sin(double a, double b);
        void cos(double a, double b);
        void tan(double a, double b);
        void asin(double a, double b);
        void acos(double a, double b);
        void atan(double a, double b);

        void log(double a, double b);
        void ln(double a, double b);

        void sqrt(double a, double b);

        void reset();
        double getData();
};

}  // namespace s21 

#endif
