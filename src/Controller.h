#ifndef EXAMPLECONTROLLER_H
#define EXAMPLECONTROLLER_H

#include "Model.h"

namespace s21 {
class Controller 
{
    private:
        CalculationModel *model;
    public:
        Controller(CalculationModel *m):model(m) {};
        double add(double a);
        double sub(double a);
        double mult(double a);
        double div(double a);
        void reset();
};

}  // namespace s21

#endif
