#include <QMessageBox>
#include "controller.h"
#include "dialog/dialog_barcodelist.h"
#include "dialog/dialog_about.h"
#include "dialog/dialog_settings.h"

Controller::Controller(ISaver *saver) : QObject()
{
  connect(this, &Controller::signalGetBarcode,
          saver, &ISaver::slotGetBarcode);
  connect(this, &Controller::signalScanBarcode,
          saver, &ISaver::slotSaveBarcode);
  connect(this, &Controller::signalGetAllBarcodeNames,
          saver, &ISaver::slotGetAllBarcodeNames);
  connect(this, &Controller::signalDeleteBarcode,
          saver, &ISaver::slotDeleteBarcode);
  connect(this, &Controller::signalDeleteAllBarcodes,
          saver, &ISaver::slotDeleteAllBarcodes);
  connect(this, &Controller::signalDeleteData,
          saver, &ISaver::slotDeleteData);
  connect(this, &Controller::signalGetSettings,
          saver, &ISaver::slotGetSettings);
  connect(this, &Controller::signalSetSettings,
          saver, &ISaver::slotSetSettings);
  initSaver(saver);
}

void Controller::initSaver(ISaver *saver)
{
  QString result = saver->init();
  if(result != nullptr)
  {
    QMessageBox::warning(nullptr, tr("Warning"), result);
  }
}

void Controller::slotListAllBarcodes()
{
  dialog::BarcodeList *dialog = new dialog::BarcodeList(this);
  dialog->show();
}

void Controller::slotShowAbout()
{
  dialog::About *dialog = new dialog::About();
  dialog->show();
}

void Controller::slotShowSettings()
{
  dialog::Settings *dialog = new dialog::Settings(this);
  dialog->show();
}
