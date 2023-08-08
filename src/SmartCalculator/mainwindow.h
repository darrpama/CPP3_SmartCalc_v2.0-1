#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qvector.h>
// <locale.h> is for normal work c++ and pure c func. See main.cpp.
// The problem is that in Qt double is 0,01 and in C double is 0.01,
// and in another systems double style can be different
#include <locale.h>

#include "credit.h"  // this is for open new widget with credit calc
#include "deposit.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include "s21_calculator.h"
#include "s21_stack.h"
#include "s21_credit_calculator.h"
#ifdef __cplusplus
}
#endif

#include "qcustomplot.h"

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
    Ui::MainWindow *ui;
    Credit credit;
    Deposit deposit;

private slots:
    void digit_and_oper();
    void func();
    void Bdot_clicked();
    void Bac_clicked();
    void Bclbr_clicked();
    void Bopbr_clicked();
    void Bdel_clicked();
    void Beq_clicked();

    void set_axis();
    void draw_graph();

    void on_Bgraphclear_clicked();
    void on_actionCredit_calc_triggered();
    void on_actionDeposit_calc_triggered();
    void keyClick(QString str);
    void keyPressEvent(QKeyEvent *e);
    void error();
    void on_pBcalculate_eq_clicked();
};
#endif // MAINWINDOW_H
