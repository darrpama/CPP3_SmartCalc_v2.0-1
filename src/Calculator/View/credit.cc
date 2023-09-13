#include "Credit.h"
#include "ui_Credit.h"

Credit::Credit(s21::Controller *c, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Credit)
{
  ui->setupUi(this);
  this->setWindowTitle("Кредитный калькулятор");
}

Credit::~Credit()
{
  delete ui;
}
