#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H
#include <math.h>
#include <stack>
#include <queue>

class CalculationModel
{
    private:
        struct Data {
            double value;
            int priority;
            char *oper;
        };
        std::stack<Data> stack;

        double answer{};
    public:
        CalculationModel():answer(0){};
        void add(double a);
        void sub(double a);
        void mult(double a);
        void div(double a);
        void mod(double a);
        void degr(double a);

        void sin(double a);
        void cos(double a);
        void tan(double a);
        void asin(double a);
        void acos(double a);
        void atan(double a);

        void log(double a);
        void ln(double a);

        void sqrt(double a);

        void reset();
        double getData();
};

#endif
