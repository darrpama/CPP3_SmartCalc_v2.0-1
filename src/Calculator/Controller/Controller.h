#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/Model.h"

namespace s21 {

class Controller 
{
    private:
        CalculationModel *model;
    public:
        Controller(CalculationModel *m):model(m) {};

        std::string Calculate(std::string);
        void Reset();
};

}  // namespace s21

#endif
