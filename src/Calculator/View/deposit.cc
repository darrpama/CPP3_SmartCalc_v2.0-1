#include "Deposit.h"
#include "ui_Deposit.h"

Deposit::Deposit(s21::Controller *c, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Deposit),
  controller(c)
{
  ui->setupUi(this);
  this->setWindowTitle("Депозитный калькулятор");
}

Deposit::~Deposit()
{
  delete ui;
}
