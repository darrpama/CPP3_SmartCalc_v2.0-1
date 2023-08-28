#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>

#ifdef __cplusplus
extern "C"
{
#endif
#include "s21_deposit_calculator.h"
#ifdef __cplusplus
}
#endif

namespace Ui {
class Deposit;
}

class Deposit : public QWidget
{
  Q_OBJECT

public:
  explicit Deposit(QWidget *parent = nullptr);
  ~Deposit();

private slots:
  void on_pBdepositCalculate_clicked();

private:
  Ui::Deposit *ui;
};

#endif // DEPOSIT_H
