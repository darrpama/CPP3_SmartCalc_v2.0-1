#include "View.h"
#include "ui_View.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->Bzero,  SIGNAL(clicked()), this, SLOT(DigitAndOper()));
  connect(ui->Bone,   SIGNAL(clicked()), this, SLOT(DigitAndOper()));
  connect(ui->Btwo,   SIGNAL(clicked()), this, SLOT(DigitAndOper()));
  connect(ui->Bthree, SIGNAL(clicked()), this, SLOT(DigitAndOper()));
  connect(ui->Bfour,  SIGNAL(clicked()), this, SLOT(DigitAndOper()));
  connect(ui->Bfive,  SIGNAL(clicked()), this, SLOT(DigitAndOper()));
  connect(ui->Bsix,   SIGNAL(clicked()), this, SLOT(DigitAndOper()));
  connect(ui->Bseven, SIGNAL(clicked()), this, SLOT(DigitAndOper()));
  connect(ui->Beight, SIGNAL(clicked()), this, SLOT(DigitAndOper()));
  connect(ui->Bnine,  SIGNAL(clicked()), this, SLOT(DigitAndOper()));
  connect(ui->Bx,     SIGNAL(clicked()), this, SLOT(DigitAndOper()));

  connect(ui->Badd,   SIGNAL(clicked()), this, SLOT(DigitAndOper()));
  connect(ui->Bsub,   SIGNAL(clicked()), this, SLOT(DigitAndOper()));
  connect(ui->Bmul,   SIGNAL(clicked()), this, SLOT(DigitAndOper()));
  connect(ui->Bdiv,   SIGNAL(clicked()), this, SLOT(DigitAndOper()));
  connect(ui->Bpow,   SIGNAL(clicked()), this, SLOT(DigitAndOper()));
  connect(ui->Bmod,   SIGNAL(clicked()), this, SLOT(DigitAndOper()));

  connect(ui->Bln,    SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->Bsin,   SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->Bcos,   SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->Btan,   SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->Blog,   SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->Basin,  SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->Bacos,  SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->Batan,  SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->Bsqrt,  SIGNAL(clicked()), this, SLOT(Func()));

  connect(ui->Beq,    SIGNAL(clicked()), this, SLOT(BEqClicked()));
  connect(ui->Bac,    SIGNAL(clicked()), this, SLOT(BAcClicked()));
  connect(ui->Bdot,   SIGNAL(clicked()), this, SLOT(BDotClicked()));
  connect(ui->Bdel,   SIGNAL(clicked()), this, SLOT(BDelClicked()));
  connect(ui->Bclbr,  SIGNAL(clicked()), this, SLOT(BClBrClicked()));
  connect(ui->Bopbr,  SIGNAL(clicked()), this, SLOT(BOpBrClicked()));


  connect(ui->Bset_axis,    SIGNAL(clicked()), this, SLOT(SetAxis()));
  connect(ui->Bdraw_graph,  SIGNAL(clicked()), this, SLOT(DrawGraph()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::DigitAndOper()
{
  QPushButton *button = (QPushButton *)sender();
  if (controller.GetError()) {
    ui->label->setText("");
  }
  ui->label->setText(ui->label->text() + button->text());
}


void MainWindow::Func()
{
  QPushButton *button = (QPushButton *)sender();
  if (controller.GetError()) {
    ui->label->setText("");
  }
  ui->label->setText(ui->label->text() + button->text() + "(");
}


void MainWindow::BDotClicked()
{
  ui->label->setText(ui->label->text() + ".");
}


void MainWindow::BAcClicked()
{
  ui->label->setText("");
  on_Bgraphclear_clicked();
}

void MainWindow::BEqClicked()
{
  QString input_string = ui->label->text();
  std::string result = "";

  try
  {
    result = controller->Calculate(input_string.toStdString());
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    result = std::to_string(e);
  }
  ui->label->setText(QString(result));
}

void MainWindow::BClBrClicked()
{
  if (controller.GetError()) {
    ui->label->setText("");
  }
    ui->label->setText(ui->label->text() + ")");
}

void MainWindow::BOpBrClicked()
{
  if (controller.GetError()) {
    ui->label->setText("");
  }
    ui->label->setText(ui->label->text() + "(");
}

void MainWindow::BDelClicked()
{
  QString new_label = ui->label->text();
  new_label.chop(1);
  ui->label->setText(new_label);
}

void MainWindow::DrawGraph() {
  QVector<double> x(1000), y(1000);
  QString input_string = ui->label->text();
  std::pair graph = controller->GetGraph();
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

void MainWindow::SetAxis()
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

void MainWindow::OnBGraphClearClicked()
{
  if (ui->widget->graph(0)) {
    ui->widget->graph(0)->data()->clear();
    ui->widget->replot();
  }
}

void MainWindow::OnActionCreditCalcTriggered()
{
  credit.show();
}

void MainWindow::OnActionDepositCalcTriggered()
{
  deposit.show();
}

void MainWindow::KeyClick(QString str)
{
    ui->label->setText(ui->label->text() + str);
}

void MainWindow::KeyPressEvent(QKeyEvent *e)
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

void MainWindow::OnPBCalculateEqClicked()
{
  QString input_string = ui->label->text();
  QString tmpStr = input_string;
  double value = ui->xValue->value();
  tmpStr.replace("x", "(" + QString::number(value, 'g', 6) + ")");

  std::string result = "";

  try
  {
    result = controller->Calculate(input_string.toStdString());
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    result = std::to_string(e);
  }
  ui->label->setText(QString(result));

}
