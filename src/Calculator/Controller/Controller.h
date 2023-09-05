#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/Model.h"

namespace s21 {

class Controller 
{
  private:
    CalculationModel *model;
  public:
    Controller(CalculationModel *m) : model(m) {};

    std::string Calculate(const std::string&);
    std::pair<std::vector<double>, std::vector<double>> GetGraph(std::string, double, double);
    void Reset();
    bool GetError();
};

}  // namespace s21

#endif
