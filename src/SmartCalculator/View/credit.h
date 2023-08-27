#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>

#ifdef __cplusplus
extern "C"
{
#endif
#include "s21_credit_calculator.h"
#ifdef __cplusplus
}
#endif

namespace Ui {
class Credit;
}

class Credit : public QWidget
{
    Q_OBJECT

public:
    explicit Credit(QWidget *parent = nullptr);
    ~Credit();

private slots:
  void on_pBcreditcalculate_clicked();

private:
    Ui::Credit *ui;
};

#endif // CREDIT_H
