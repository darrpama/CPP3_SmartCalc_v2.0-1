#include "View/View.h"
#include "View/Credit.h"
#include "View/Deposit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  setenv("LC_NUMERIC", "C", 1);
  QApplication a(argc, argv);
  s21::Model model;
  s21::CreditModel creditModel;
  s21::Controller controller(&model, &creditModel);
  View view(&controller);
  view.show();
  return a.exec();
}
