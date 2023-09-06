#include "View/View.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  setenv("LC_NUMERIC", "C", 1);
  QApplication a(argc, argv);
  s21::CalculationModel model;
  s21::Controller controller(&model);
  View view(&controller);
  view.show();
  return a.exec();
}