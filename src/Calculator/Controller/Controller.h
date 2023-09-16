#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/Model.h"
#include "../Model/CreditModel.h"

namespace s21 {

class Controller 
{ 
  public:
    Controller(Model *m, CreditModel *cm) : model(m), creditModel(cm) {};

    std::string Calculate(const std::string&);
    std::pair<std::vector<double>, std::vector<double>> GetGraph(std::string, double, double);
    credit_data CalculateCredit(double, double, double, time_type, credit_type);
    void ResetCalculatorModel();
    void ResetCreditModel();
    bool GetError();

  private:
    Model *model;
    CreditModel *creditModel;
};

}  // namespace s21

#endif
