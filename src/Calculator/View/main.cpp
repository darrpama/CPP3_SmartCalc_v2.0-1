#include "View.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  s21::CalculationModel model;
  s21::Controller controller(&model);
  


  setenv("LC_NUMERIC", "C", 1);
  QApplication a(argc, argv);
  View w;
  w.show();
  return a.exec();
}
