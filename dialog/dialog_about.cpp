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
  ui->lbVersion->setText(QString("Version: %1.%2.%3.%4")
                         .arg(VERSION_MAJOR)
                         .arg(VERSION_MINOR)
                         .arg(VERSION_PATCH)
                         .arg(GIT_CURRENT));
}

About::~About()
{
  delete ui;
}
}//namespace dialog
