#include "View/View.h"
#include <iostream>
#include "ui_View.h"

View::View(QWidget *parent, s21::Controller *c)
  : QMainWindow(parent), controller(c), ui(new Ui::View)
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

View::~View()
{
  delete ui;
}

void View::DigitAndOper()
{
  QPushButton *button = (QPushButton *)sender();
  if (controller->GetError()) {
    ui->label->setText("");
  }
  ui->label->setText(ui->label->text() + button->text());
}


void View::Func()
{
  QPushButton *button = (QPushButton *)sender();
  if (controller->GetError()) {
    ui->label->setText("");
  }
  ui->label->setText(ui->label->text() + button->text() + "(");
}


void View::BDotClicked()
{
  ui->label->setText(ui->label->text() + ".");
}


void View::BAcClicked()
{
  ui->label->setText("");
  OnBGraphClearClicked();
}

void View::BEqClicked()
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
    result = e.what();
  }
  ui->label->setText(QString::fromStdString(result));
}

void View::BClBrClicked()
{
  if (controller->GetError()) {
    ui->label->setText("");
  }
    ui->label->setText(ui->label->text() + ")");
}

void View::BOpBrClicked()
{
  if (controller->GetError()) {
    ui->label->setText("");
  }
    ui->label->setText(ui->label->text() + "(");
}

void View::BDelClicked()
{
  QString new_label = ui->label->text();
  new_label.chop(1);
  ui->label->setText(new_label);
}

void View::DrawGraph() {
//  QVector<double> vector();
  QString inputString = ui->label->text();

  double xMin = ui->xmin_spinbox->value();
  double xMax = ui->xmax_spinbox->value();
  std::string stdInputString(inputString.toStdString());

  
  std::vector<std::pair<double, double>> stdGraph = controller->GetGraph(stdInputString, xMin, xMax);
  QVector<std::pair<double, double>> graph = QVector<std::pair<double, double>>(stdGraph.begin(), stdGraph.end());

  for (size_t i = 0; i < graph.size(); i++)
  {
    std::cout << graph[i].first << " | " << graph[i].second << std::endl;
  }
  
  // for (int i = 0; i < 1000; i++) {
  //   QString tmpStr = input_string;
  //   tmpStr.replace("x", "(" + QString::number(x_array[i], 'g', 6) + ")");
  //   QByteArray b_str = tmpStr.toLocal8Bit();
  //   char *input_str = b_str.data();
  //   if (is_correct(input_str)) {
  //     error();
  //     break;
  //   }
  //   Data tmp = Begin(input_str);
  //   y_array[i] = tmp.value;
  //   y[i] = y_array[i];
  // }

//  SetAxis();
//  ui->widget->clearGraphs();
//  ui->widget->addGraph();
////  ui->widget->graph(0)->addData(x, y);
//  ui->widget->replot();
//  ui->widget->setInteraction(QCP::iRangeZoom, true);
//  ui->widget->setInteraction(QCP::iRangeDrag, true);
//  x.clear();
//  y.clear();
}

void View::SetAxis()
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

void View::OnBGraphClearClicked()
{
  if (ui->widget->graph(0)) {
    ui->widget->graph(0)->data()->clear();
    ui->widget->replot();
  }
}

void View::OnActionCreditCalcTriggered()
{
//  credit.show();
}

void View::OnActionDepositCalcTriggered()
{
//  deposit.show();
}

void View::KeyClick(QString str)
{
    ui->label->setText(ui->label->text() + str);
}

void View::KeyPressEvent(QKeyEvent *e)
{
  switch (e->key()) {
  case Qt::Key_Escape:
    BAcClicked();
    break;
  case Qt::Key_Asterisk:
    KeyClick("*");
    break;
  case Qt::Key_Slash:
    KeyClick("/");
    break;
  case Qt::Key_Plus:
    KeyClick("+");
    break;
  case Qt::Key_Minus:
    KeyClick("-");
    break;
  case Qt::Key_0:
    KeyClick("0");
    break;
  case Qt::Key_1:
    KeyClick("1");
    break;
  case Qt::Key_2:
    KeyClick("2");
    break;
  case Qt::Key_3:
    KeyClick("3");
    break;
  case Qt::Key_4:
    KeyClick("4");
    break;
  case Qt::Key_5:
    KeyClick("5");
    break;
  case Qt::Key_6:
    KeyClick("6");
    break;
  case Qt::Key_7:
    KeyClick("7");
    break;
  case Qt::Key_8:
    KeyClick("8");
    break;
  case Qt::Key_9:
    KeyClick("9");
    break;
  case Qt::Key_X:
    KeyClick("x");
    break;
  case Qt::Key_Period:
    KeyClick(".");
    break;
  case Qt::Key_AsciiCircum:
    KeyClick("^");
    break;
  case Qt::Key_Backspace:
    BDelClicked();
    break;
  case Qt::Key_Delete:
    BAcClicked();
    break;
  case Qt::Key_Return:
    BEqClicked();
    break;
  case Qt::Key_ParenLeft:
    KeyClick("(");
    break;
  case Qt::Key_ParenRight:
    KeyClick(")");
    break;
  }
}

void View::OnPBCalculateEqClicked()
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
    result = e.what();
  }
  ui->label->setText(QString::fromStdString(result));

}
