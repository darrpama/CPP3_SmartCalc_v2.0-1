#include "deposit.h"
#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Deposit)
{
  ui->setupUi(this);
}

Deposit::~Deposit()
{
  delete ui;
}

void Deposit::on_pBdepositCalculate_clicked()
{
  deposit_data data = {0, NULL, 0};
  double time = ui->tEtime->toPlainText().toUInt();
  double percent = ui->tEpercent->toPlainText().toDouble();
  double sum = ui->tEsum->toPlainText().toDouble();
  int kap = ui->cBkap->isChecked() ? 1 : 0;
  int time_type = ui->cBtime_type->currentIndex() ? 0 : 1;
  int kap_type  = ui->rBmonth->isChecked() ? 0 : 1;
  int ceil_time = ceil(time);
  if (time_type) {
    ceil_time *= 12;
  }

//  ui->tEsum->setText("");
//  ui->tEpercent->setText("");
//  ui->tEtime->setText("");
  ui->tEmonth->setText("");
  if (sum <= 0 || time <= 0 || percent <= 0) {
    ui->ltotalsum->setText("Пожалуйста, введите корректные данные (все переменные >= 0, время - целое число месяцев или лет)");
  } else if (sum >= 100000000 || ceil_time >= 12 * 80 || percent >= 50) {
      ui->tEmonth->setText("Пожалуйста, введите корректные данные (сумма < 100000000, время < 80 лет, проценты < 50%)");
  } else {
    if (kap_type == 0) {
      data = deposit_calculator_mounth(sum, time, percent, time_type, kap);
    } else {
      data = deposit_calculator_quartal(sum, time, percent, time_type, kap);
    }
    ui->lprofit->setText("Доход за весь срок: " + QString::number(data.profit, 'f', 2));
    ui->ltotalsum->setText("Общая сумма в конце срока: " + QString::number(data.total_sum, 'f', 2));
    for (int i = 0; i < ceil_time; i++) {
      ui->tEmonth->append(QString::number(i + 1) + " месяц: " + QString::number(data.montly_pay[i], 'f', 2) + " р.");
    }
    free(data.montly_pay);
  }
}
