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
  explicit Deposit(s21::Controller *c, QWidget *parent = nullptr);
  ~Deposit();

private slots:
//  void onPBdepositCalculateClicked();

private:
  Ui::Deposit *ui;
  s21::Controller *controller;
};

#endif // DEPOSIT_H
