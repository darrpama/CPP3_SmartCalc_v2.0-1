#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qvector.h>

// <locale.h> is for normal work c++ and pure c func. See main.cpp.
// The problem is that in Qt double is 0,01 and in C double is 0.01,
// and in another systems double style can be different
#include <locale.h>

// #include "credit.h"  // this is for open new widget with credit calc
// #include "deposit.h"

#ifdef __cplusplus
extern "C"
{
#endif


#ifdef __cplusplus
}
#endif

#include "../Controller/Controller.h"
#include "../qcustomplot/qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    s21::Controller *controller;
    Ui::MainWindow *ui;
//    Credit credit;
//    Deposit deposit;

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
    void KeyPressEvent(QKeyEvent *e);
//    void Error();
    void OnPBCalculateEqClicked();
};
#endif // MAINWINDOW_H
