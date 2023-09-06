#include "View.h"

View::View(s21::Controller *c, QWidget *parent)
  : ui(new Ui::View), controller(c)
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
  controller->Reset();
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
  QString inputString = ui->label->text();
  double xMin = ui->xmin_spinbox->value();
  double xMax = ui->xmax_spinbox->value();
  std::string stdInputString(inputString.toStdString());

  std::pair<std::vector<double>, std::vector<double>> stdGraph = controller->GetGraph(stdInputString, xMin, xMax);

//  for (size_t i = 0; i < graph.size(); i++)
//  {
//    std::cout << graph[i].first << " | " << graph[i].second << std::endl;
//  }
  
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

  SetAxis();
  ui->widget->clearGraphs();
  ui->widget->addGraph();
//  ui->widget->graph(0)->addData();
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

void View::on_pBcalculate_eq_clicked()
{
  QString input_string = ui->label->text();
  QString tmpStr = input_string;
  double value = ui->xValue->value();
  tmpStr.replace("x", "(" + QString::number(value, 'g', 6) + ")");

  std::string result = "";

  try
  {
    result = controller->Calculate(tmpStr.toStdString());
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    result = e.what();
  }

  ui->label->setText(QString::fromStdString(result));

}

