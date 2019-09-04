#include <QMessageBox>
#include "dialog_barcodelist.h"
#include "ui_dialog_barcodelist.h"
#include "barcode.hpp"

namespace dialog
{
BarcodeList::BarcodeList(Controller *controller) :
  QDialog(),
  ui(new Ui::BarcodeList)
{
  ui->setupUi(this);
  connect(ui->pbShow, &QPushButton::clicked,
          this, &BarcodeList::slotShowBarcode);
  connect(this, &BarcodeList::signalShowBarcode,
          controller, &Controller::signalShowBarcode);
  connect(this, &BarcodeList::signalGetAllBarcodeNames,
          controller, &Controller::signalGetAllBarcodeNames);
  connect(ui->pbDelete, &QPushButton::clicked,
          this, &BarcodeList::slotDeleteSelected);
  connect(this, &BarcodeList::signalDeleteBarcode,
          controller, &Controller::signalDeleteBarcode);
  connect(controller, &Controller::signalScanBarcode,
          this, &BarcodeList::slotReloadList);
  connect(ui->lwList, &QListWidget::doubleClicked,
          this, &BarcodeList::slotShowBarcode);
  connect(ui->pbDeleteAll, &QPushButton::clicked,
          this, &dialog::BarcodeList::slotDeleteAllPressed);
  connect(this, &dialog::BarcodeList::signalDeleteAllBarcodes,
          controller, &Controller::signalDeleteAllBarcodes);
  connect(controller, &Controller::signalDeleteData,
          this, &dialog::BarcodeList::slotReloadList);
  initList();
}

BarcodeList::~BarcodeList()
{
  delete ui;
}

void BarcodeList::slotDeleteSelected()
{
  if(ui->lwList->selectedItems().count() == 0)
  {
    return;
  }
  QString barcode = ui->lwList->currentItem()->text();
  QMessageBox::StandardButton reply = QMessageBox::question(
        this, tr("Are You Sure?"),
        tr("if you delete it, you will lose all data which about ") + barcode,
        QMessageBox::Yes|QMessageBox::No);
  if(reply == QMessageBox::Yes)
  {
    emit signalDeleteBarcode(barcode);
    initList();
  }
}

void BarcodeList::slotDeleteAllPressed()
{
  QMessageBox::StandardButton reply = QMessageBox::question(
        this, tr("Are You Sure?"),
        tr("Do you want to remove all of data? This operation can NOT undo."),
        QMessageBox::Yes|QMessageBox::No);
  if(reply == QMessageBox::Yes)
  {
    emit signalDeleteAllBarcodes();
    initList();
  }
}

void BarcodeList::slotReloadList()
{
  initList();
}

void BarcodeList::slotShowBarcode()
{
  if(ui->lwList->selectedItems().count() == 0)
  {
    return;
  }
  emit signalShowBarcode(ui->lwList->currentItem()->text());
}


void BarcodeList::initList()
{
  QVector<QString> barcodes = emit signalGetAllBarcodeNames();
  ui->lwList->clear();
  for(auto barcode : barcodes)
  {
    ui->lwList->addItem(barcode);
  }
}
}//namespace dialog
