#include "Credit.h"
#include "ui_Credit.h"

using namespace s21;

Credit::Credit(Controller *c, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Credit),
  controller(c)
{
  ui->setupUi(this);
  this->setWindowTitle("Кредитный калькулятор");

  connect(ui->pBcreditCalculate, SIGNAL(clicked()), this, SLOT(OnBCreditCalculateClicked()));

}

Credit::~Credit()
{
  delete ui;
}

void Credit::OnBCreditCalculateClicked()
{
  double time = ui->tEtime->toPlainText().toUInt();
  double percent = ui->tEpercent->toPlainText().toDouble();
  double sum = ui->tEsum->toPlainText().toDouble();
  credit_type creditType = ui->rBannuitent->isChecked() ? annuitet : differential;
  credit_time_type timeType = ui->cBtime_type->currentIndex() ? credit_time_type::credit_month : credit_time_type::credit_year;
  int ceil_time = ceil(time);

  ui->tEmonth->setText("");
  if (timeType == credit_time_type::credit_year)
  {
    ceil_time *= 12;
  }
  if (sum <= 0 || time <= 0 || percent <= 0)
  {
    ui->tEmonth->setText("Пожалуйста, введите корректные данные (все переменные > 0, время - целое число месяцев или лет)");
  }
  else if (sum >= 100000000 || ceil_time >= 12 * 80 || percent >= 50)
  {
    ui->tEmonth->setText("Пожалуйста, введите корректные данные (сумма < 100000000, время < 80 лет, проценты < 50%)");
  }
  else
  {
    s21::credit_data data = controller->CalculateCredit(sum, time, percent, timeType, creditType);
    if (creditType == s21::annuitet) {
      ui->Lmonthpay->setText("Платёж в месяц: " + QString::number(data.monthly_pay.back(), 'f', 2));
    } else {
      double max = data.monthly_pay.front();
      double min = max;
      for (auto it = data.monthly_pay.begin(); it != data.monthly_pay.end(); ++it) {
        if (max < *it) {
          max = *it;
        }
        if (min > *it)
          min = *it;
      }
      ui->Lmonthpay->setText("Платёж в месяц: " + QString::number(min, 'f', 2) + " .. " + QString::number(max, 'f', 2));
    }
    int i = 0;
    for (auto it = data.monthly_pay.begin(); it != data.monthly_pay.end(); ++it, i++) {
      ui->tEmonth->append(QString::number(i + 1) + " месяц: " + QString::number(*it, 'f', 2) + " р.");
    }
    ui->Loverpay->setText("Переплата: " + QString::number(data.overpay, 'f', 2));
  }
}

