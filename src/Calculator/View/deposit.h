#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QDialog>

#include "../Controller/Controller.h"

namespace Ui {
class Deposit;
}

class Deposit : public QDialog
{
  Q_OBJECT

public:
  Deposit(s21::Controller *c, QWidget *parent = nullptr);
  ~Deposit();

private slots:
  void OnBDepositCalculateClicked();

private:
  s21::Controller *controller;
  Ui::Deposit *ui;
};

#endif // DEPOSIT_H
