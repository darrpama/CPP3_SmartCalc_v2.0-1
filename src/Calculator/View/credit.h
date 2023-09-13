#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>

#include "../Controller/Controller.h"

#ifdef __cplusplus
extern "C"
{
#endif
//#include "s21_credit_calculator.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class Credit; }
QT_END_NAMESPACE

class Credit : public QDialog
{
    Q_OBJECT

public:
    explicit Credit(s21::Controller *c, QWidget *parent = nullptr);
    ~Credit();


private slots:
//  void on_pBcreditcalculate_clicked();

private:
    Ui::Credit *ui;
};

#endif // CREDIT_H
