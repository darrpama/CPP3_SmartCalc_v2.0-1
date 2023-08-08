#include "credit.h"
#include "ui_credit.h"

Credit::Credit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Credit)
{
    ui->setupUi(this);
}

Credit::~Credit()
{
    delete ui;
}

void Credit::on_pBcreditcalculate_clicked()
{
    credit_data data = {0, NULL, 0};
    double time = ui->tEtime->toPlainText().toUInt();
    double percent = ui->tEpercent->toPlainText().toDouble();
    double sum = ui->tEsum->toPlainText().toDouble();
    int type = ui->rBannuitent->isChecked() ? 0 : 1;
    int time_type = ui->cBtime_type->currentIndex() ? 0 : 1;
//    double mutalpay = 0.0, overpay = 0.0;
    int ceil_time = ceil(time);
    if (time_type) {
      ceil_time *= 12;
    }
//    double every_month[ceil_time];

//    ui->tEsum->setText("");
//    ui->tEtime->setText("");
//    ui->tEpercent->setText("");
    ui->tEmonth->setText("");
    if (sum <= 0 || time <= 0 || percent <= 0) {
      ui->tEmonth->setText("Пожалуйста, введите корректные данные (все переменные > 0, время - целое число месяцев или лет)");
    } else if (sum >= 100000000 || ceil_time >= 12 * 80 || percent >= 50) {
      ui->tEmonth->setText("Пожалуйста, введите корректные данные (сумма < 100000000, время < 80 лет, проценты < 50%)");
    } else {
      if (type == 0) {
        data = credit_calculator_anuitet(sum, time, percent, time_type);
        ui->Lmonthpay->setText("Платёж в месяц: " + QString::number(data.monthly_pay[0], 'f', 2));
      } else {
        data = credit_calculator_differ(sum, time, percent, time_type);
        double max = data.monthly_pay[0];
        double min = data.monthly_pay[0];
        for (int i = 0; i < ceil_time; i++) {
          if (max < data.monthly_pay[i]) {
            max = data.monthly_pay[i];
          }
          if (min > data.monthly_pay[i])
            min = data.monthly_pay[i];
        }
        ui->Lmonthpay->setText("Платёж в месяц: " + QString::number(min, 'f', 2) + " .. " + QString::number(max, 'f', 2));
      }
      for (int i = 0; i < ceil_time; i++) {
        ui->tEmonth->append(QString::number(i + 1) + " месяц: " + QString::number(data.monthly_pay[i], 'f', 2) + " р.");
      }
      if (data.monthly_pay != NULL) {
        free(data.monthly_pay);
      }
      ui->Loverpay->setText("Переплата: " + QString::number(data.overpay, 'f', 2));
    }
}
