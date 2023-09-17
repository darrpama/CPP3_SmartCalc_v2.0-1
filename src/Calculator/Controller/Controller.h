#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/Model.h"
#include "../Model/CreditModel.h"
#include "../Model/DepositModel.h"

namespace s21 {

class Controller 
{ 
  public:
    Controller(Model *m, CreditModel *cm, DepositModel *dm) : model(m), creditModel(cm), depositModel(dm) {};

    std::string Calculate(const std::string&);
    std::pair<std::vector<double>, std::vector<double>> GetGraph(std::string, double, double);
    credit_data CalculateCredit(double, double, double, credit_time_type, credit_type);
    deposit_data CalculateDeposit(double sum, double time, double percent,
                    deposit_time_type timeType, capitalization capitalization,
                    deposit_time_type capitalization_period);
    void ResetCalculatorModel();
    bool GetError();

  private:
    Model *model;
    CreditModel *creditModel;
    DepositModel *depositModel;
};

}  // namespace s21

#endif
