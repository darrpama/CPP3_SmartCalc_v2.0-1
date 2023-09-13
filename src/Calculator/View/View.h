#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <qvector.h>

#include <locale.h>
#include <iostream>

#include "Credit.h"
#include "Deposit.h"
#include "./ui_View.h"

#include "../Controller/Controller.h"
#include "../qcustomplot/qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
  Q_OBJECT

public:
  View(s21::Controller *c, QWidget *parent = nullptr);
  ~View();
private:
  s21::Controller *controller;
  Ui::View *ui;
  Credit* creditView;
  Deposit* depositView;

private slots:
  void DigitAndOper();
  void Func();
  void BDotClicked();
  void BAcClicked();
  void BClBrClicked();
  void BOpBrClicked();
  void BDelClicked();
  void BEqClicked();

  void SetAxis();
  void DrawGraph();

  void OnBGraphClearClicked();
  void OnActionCreditCalcTriggered();
  void OnActionDepositCalcTriggered();
  void KeyClick(QString str);
  void OnBCalculateEqClicked();
};

#endif // VIEW_H
