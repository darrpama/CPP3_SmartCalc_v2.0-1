#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>

#include "../Controller/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Credit; }
QT_END_NAMESPACE

class Credit : public QDialog
{
  Q_OBJECT

 public:
  Credit(s21::Controller *c, QWidget *parent = nullptr);
  ~Credit();


 private slots:
  void OnBCreditCalculateClicked();

 private:
  s21::Controller *controller;
  Ui::Credit *ui;
};

#endif // CREDIT_H
