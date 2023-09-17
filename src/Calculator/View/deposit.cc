#include "Deposit.h"
#include "ui_Deposit.h"

using namespace s21;

Deposit::Deposit(s21::Controller *c, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Deposit),
  controller(c)
{
  ui->setupUi(this);
  this->setWindowTitle("Депозитный калькулятор");

  connect(ui->pBdepositCalculate, SIGNAL(clicked()), this, SLOT(OnBDepositCalculateClicked()));
}

Deposit::~Deposit()
{
  delete ui;
}

void Deposit::OnBDepositCalculateClicked()
{
  double time = ui->tEtime->toPlainText().toUInt();
  double percent = ui->tEpercent->toPlainText().toDouble();
  double sum = ui->tEsum->toPlainText().toDouble();
  capitalization capitalization = ui->rBmonth->isChecked() ? with_capitalization : without_capitalization;
  deposit_time_type timeType = ui->cBtime_type->currentIndex() ? deposit_time_type::deposit_month : deposit_time_type::deposit_year;

  deposit_time_type capitalizationPeriod = deposit_time_type::deposit_month;

  if (ui->rBquartal->isChecked())
  {
    capitalizationPeriod = deposit_time_type::deposit_quartal;
  }
  else if (ui->rByear->isChecked())
  {
    capitalizationPeriod = deposit_time_type::deposit_year;
  }

  int ceil_time = ceil(time);
  if (timeType == deposit_time_type::deposit_year) {
    ceil_time *= 12;
  }

  ui->tEmonth->setText("");
  if (sum <= 0 || time <= 0 || percent <= 0) {
    ui->ltotalsum->setText("Пожалуйста, введите корректные данные (все переменные >= 0, время - целое число месяцев или лет)");
  } else if (sum >= 100000000 || ceil_time >= 12 * 80 || percent >= 50) {
      ui->tEmonth->setText("Пожалуйста, введите корректные данные (сумма < 100000000, время < 80 лет, проценты < 50%)");
  } else {
    deposit_data data  = controller->CalculateDeposit(sum, time, percent, timeType, capitalization, capitalizationPeriod);

    ui->lprofit->setText("Доход за весь срок: " + QString::number(data.profit, 'f', 2));
    ui->ltotalsum->setText("Общая сумма в конце срока: " + QString::number(data.total_sum, 'f', 2));
    int i = 0;
    for (auto it = data.monthly_profit.begin(); it != data.monthly_profit.end(); ++it, ++i) {
      ui->tEmonth->append(QString::number(i + 1) + " месяц: " + QString::number(*it, 'f', 2) + " р.");
    }
  }
}
