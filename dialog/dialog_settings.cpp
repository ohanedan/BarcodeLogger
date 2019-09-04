#include <QMessageBox>
#include "dialog_settings.h"
#include "ui_dialog_settings.h"

namespace dialog
{
Settings::Settings(Controller *controller) :
  QDialog(),
  ui(new Ui::Settings)
{
  ui->setupUi(this);
  connect(this, &Settings::signalGetSettings,
          controller, &Controller::signalGetSettings);
  connect(this, &Settings::signalSetSettings,
          controller, &Controller::signalSetSettings);
  connect(ui->pbSave, &QPushButton::clicked,
          this, &Settings::slotSaveData);
  connect(ui->pbCancel, &QPushButton::clicked,
          this, &Settings::close);
  mSettings = emit signalGetSettings();
  init();
}

Settings::~Settings()
{
  delete ui;
}

void Settings::init()
{
  ui->cbLang->setCurrentText(mSettings->getLang());
  ui->cbAutoFocus->setChecked(mSettings->getAutoFocus());
}

void Settings::slotSaveData()
{
  if(ui->cbLang->currentText() != mSettings->getLang())
  {
    QMessageBox::information(this,
                          tr("Language Changed"),
                          tr("Please restart application "
                             "for changing language."));
  }
  emit signalSetSettings(std::make_shared<::Settings>(
                           ui->cbLang->currentText(),
                           ui->cbAutoFocus->isChecked()));
  this->close();
}
}//namespace dialog
