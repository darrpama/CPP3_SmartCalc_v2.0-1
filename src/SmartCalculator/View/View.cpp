#include "View.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->Bzero,  SIGNAL(clicked()), this, SLOT(digit_and_oper()));
  connect(ui->Bone,   SIGNAL(clicked()), this, SLOT(digit_and_oper()));
  connect(ui->Btwo,   SIGNAL(clicked()), this, SLOT(digit_and_oper()));
  connect(ui->Bthree, SIGNAL(clicked()), this, SLOT(digit_and_oper()));
  connect(ui->Bfour,  SIGNAL(clicked()), this, SLOT(digit_and_oper()));
  connect(ui->Bfive,  SIGNAL(clicked()), this, SLOT(digit_and_oper()));
  connect(ui->Bsix,   SIGNAL(clicked()), this, SLOT(digit_and_oper()));
  connect(ui->Bseven, SIGNAL(clicked()), this, SLOT(digit_and_oper()));
  connect(ui->Beight, SIGNAL(clicked()), this, SLOT(digit_and_oper()));
  connect(ui->Bnine,  SIGNAL(clicked()), this, SLOT(digit_and_oper()));
  connect(ui->Bx,     SIGNAL(clicked()), this, SLOT(digit_and_oper()));

  connect(ui->Badd,   SIGNAL(clicked()), this, SLOT(digit_and_oper()));
  connect(ui->Bsub,   SIGNAL(clicked()), this, SLOT(digit_and_oper()));
  connect(ui->Bmul,   SIGNAL(clicked()), this, SLOT(digit_and_oper()));
  connect(ui->Bdiv,   SIGNAL(clicked()), this, SLOT(digit_and_oper()));
  connect(ui->Bpow,   SIGNAL(clicked()), this, SLOT(digit_and_oper()));
  connect(ui->Bmod,   SIGNAL(clicked()), this, SLOT(digit_and_oper()));

  connect(ui->Bln,    SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Bsin,   SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Bcos,   SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Btan,   SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Blog,   SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Basin,  SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Bacos,  SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Batan,  SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Bsqrt,  SIGNAL(clicked()), this, SLOT(func()));

  connect(ui->Beq,    SIGNAL(clicked()), this, SLOT(Beq_clicked()));
  connect(ui->Bac,    SIGNAL(clicked()), this, SLOT(Bac_clicked()));
  connect(ui->Bdot,   SIGNAL(clicked()), this, SLOT(Bdot_clicked()));
  connect(ui->Bdel,   SIGNAL(clicked()), this, SLOT(Bdel_clicked()));
  connect(ui->Bclbr,  SIGNAL(clicked()), this, SLOT(Bclbr_clicked()));
  connect(ui->Bopbr,  SIGNAL(clicked()), this, SLOT(Bopbr_clicked()));


  connect(ui->Bset_axis,    SIGNAL(clicked()), this, SLOT(set_axis()));
  connect(ui->Bdraw_graph,  SIGNAL(clicked()), this, SLOT(draw_graph()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::digit_and_oper()
{
  QPushButton *button = (QPushButton *)sender();
  if (ui->label->text().contains("Wrong") || ui->label->text().contains("Err") || ui->label->text().contains("nan")) {
    ui->label->setText("");
  }
  ui->label->setText(ui->label->text() + button->text());
}


void MainWindow::func()
{
  QPushButton *button = (QPushButton *)sender();
  if (ui->label->text().contains("Wrong") || ui->label->text().contains("Err") || ui->label->text().contains("nan")) {
    ui->label->setText("");
  }
  ui->label->setText(ui->label->text() + button->text() + "(");
}


void MainWindow::Bdot_clicked()
{
  ui->label->setText(ui->label->text() + ".");
}


void MainWindow::Bac_clicked()
{
  ui->label->setText("");
  on_Bgraphclear_clicked();
}

void MainWindow::Beq_clicked()
{
  QString input_string = ui->label->text();
  QByteArray b_str = input_string.toLocal8Bit();
  char *input_str = b_str.data();
  if (is_correct(input_str) || input_string.contains("Wrong expression")) {
    error();
  } else {
    if (ui->label->text().contains("x")) {
      draw_graph();
    } else {
      Data res = Begin(input_str);
      if (IsError(res)) {
        ui->label->clear();
        ui->label->setText(ui->label->text() + "Error");
      } else {
        ui->label->setText(QString::number(res.value, 'f', 6));
      }
    }
  }
}

void MainWindow::error() {
    ui->label->clear();
    ui->label->setText("Wrong expression");
}

void MainWindow::Bclbr_clicked()
{
  if (ui->label->text().contains("Wrong") || ui->label->text().contains("Err") || ui->label->text().contains("nan")) {
    ui->label->setText("");
  }
    ui->label->setText(ui->label->text() + ")");
}

void MainWindow::Bopbr_clicked()
{
  if (ui->label->text().contains("Wrong") || ui->label->text().contains("Err") || ui->label->text().contains("nan")) {
    ui->label->setText("");
  }
    ui->label->setText(ui->label->text() + "(");
}

void MainWindow::Bdel_clicked()
{
  QString new_label = ui->label->text();
  new_label.chop(1);
  ui->label->setText(new_label);
}

void MainWindow::draw_graph() {
  QVector<double> x(1000), y(1000);
  QString input_string = ui->label->text();
  double x_min = ui->xmin_spinbox->value();
  double x_max = ui->xmax_spinbox->value();
  double x_array[1000] = {0};
  double y_array[1000] = {0};

  for (int i = 0; i < 1000; i++) {
    x_array[i] = x_min + i * (x_max - x_min) / 1000;
    x[i] = x_array[i];
  }

  for (int i = 0; i < 1000; i++) {
    QString tmpStr = input_string;
    tmpStr.replace("x", "(" + QString::number(x_array[i], 'g', 6) + ")");
    QByteArray b_str = tmpStr.toLocal8Bit();
    char *input_str = b_str.data();
    if (is_correct(input_str)) {
      error();
      break;
    }
    Data tmp = Begin(input_str);
    y_array[i] = tmp.value;
    y[i] = y_array[i];
  }

  set_axis();
  ui->widget->clearGraphs();
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  x.clear();
  y.clear();
}

void MainWindow::set_axis()
{
  double x_min = ui->xmin_spinbox->value();
  double x_max = ui->xmax_spinbox->value();
  double y_min = ui->ymin_spinbox->value();
  double y_max = ui->ymax_spinbox->value();
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  ui->widget->xAxis->setRangeLower(x_min);
  ui->widget->xAxis->setRangeUpper(x_max);
  ui->widget->yAxis->setRangeLower(y_min);
  ui->widget->yAxis->setRangeUpper(y_max);
  ui->widget->replot();
}

void MainWindow::on_Bgraphclear_clicked()
{
  if (ui->widget->graph(0)) {
    ui->widget->graph(0)->data()->clear();
    ui->widget->replot();
  }
}

void MainWindow::on_actionCredit_calc_triggered()
{
  credit.show();
}

void MainWindow::on_actionDeposit_calc_triggered()
{
  deposit.show();
}

void MainWindow::keyClick(QString str)
{
    ui->label->setText(ui->label->text() + str);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
  switch (e->key()) {
  case Qt::Key_Escape:
    Bac_clicked();
    break;
  case Qt::Key_Asterisk:
    keyClick("*");
    break;
  case Qt::Key_Slash:
    keyClick("/");
    break;
  case Qt::Key_Plus:
    keyClick("+");
    break;
  case Qt::Key_Minus:
    keyClick("-");
    break;
  case Qt::Key_0:
    keyClick("0");
    break;
  case Qt::Key_1:
    keyClick("1");
    break;
  case Qt::Key_2:
    keyClick("2");
    break;
  case Qt::Key_3:
    keyClick("3");
    break;
  case Qt::Key_4:
    keyClick("4");
    break;
  case Qt::Key_5:
    keyClick("5");
    break;
  case Qt::Key_6:
    keyClick("6");
    break;
  case Qt::Key_7:
    keyClick("7");
    break;
  case Qt::Key_8:
    keyClick("8");
    break;
  case Qt::Key_9:
    keyClick("9");
    break;
  case Qt::Key_X:
    keyClick("x");
    break;
  case Qt::Key_Period:
    keyClick(".");
    break;
  case Qt::Key_AsciiCircum:
    keyClick("^");
    break;
  case Qt::Key_Backspace:
    Bdel_clicked();
    break;
  case Qt::Key_Delete:
    Bac_clicked();
    break;
  case Qt::Key_Return:
    Beq_clicked();
    break;
  case Qt::Key_ParenLeft:
    keyClick("(");
    break;
  case Qt::Key_ParenRight:
    keyClick(")");
    break;
  }
}

void MainWindow::on_pBcalculate_eq_clicked()
{
  QString input_string = ui->label->text();
  QString tmpStr = input_string;
  double value = ui->xValue->value();
  tmpStr.replace("x", "(" + QString::number(value, 'g', 6) + ")");
  QByteArray b_str = tmpStr.toLocal8Bit();
  char *input_str = b_str.data();
  if (is_correct(input_str)) {
    error();
  } else {
    Data res = Begin(input_str);
    if (IsError(res)) {
      error();
    } else {
      ui->label->setText(QString::number(res.value, 'f', 6));
    }
  }
}
