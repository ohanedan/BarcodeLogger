#include "dialog_about.h"
#include "ui_dialog_about.h"

namespace dialog
{
About::About(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::About)
{
  ui->setupUi(this);
  this->setFixedSize(this->size());
}

About::~About()
{
  delete ui;
}
}//namespace dialog
