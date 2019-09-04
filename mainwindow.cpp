#include <QMessageBox>
#include "mainwindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(Controller *controller, std::shared_ptr<Settings> s) :
  QMainWindow(),
  ui(new Ui::MainWindow), mIsScan(false)
{
  ui->setupUi(this);
  connect(ui->pbScan, &QPushButton::clicked,
          this, &MainWindow::slotScanButtonClicked);
  connect(ui->pbSearch, &QPushButton::clicked,
          this, &MainWindow::slotSearchButtonClicked);
  connect(ui->leBarcode, &QLineEdit::returnPressed,
          this, &MainWindow::slotBarcodeEntered);
  connect(this, &MainWindow::signalScanBarcode,
          controller, &Controller::signalScanBarcode);
  connect(this, &MainWindow::signalGetBarcode,
          controller, &Controller::signalGetBarcode);
  connect(ui->pbBarcodes, &QPushButton::clicked,
          controller, &Controller::slotListAllBarcodes);
  connect(controller, &Controller::signalShowBarcode,
          this, &MainWindow::slotShowBarcode);
  connect(controller, &Controller::signalDeleteBarcode,
          this, &MainWindow::slotBarcodeDeleted);
  connect(ui->pbDelete, &QPushButton::clicked,
          this, &MainWindow::slotDeleteData);
  connect(this, &MainWindow::signalDeleteData,
          controller, &Controller::signalDeleteData);
  connect(ui->pbAbout, &QPushButton::clicked,
          controller, &Controller::slotShowAbout);
  connect(ui->pbSettings, &QPushButton::clicked,
          controller, &Controller::slotShowSettings);
  connect(controller, &Controller::signalSetSettings,
          this, &MainWindow::slotSettingsChanged);
  connect(controller, &Controller::signalDeleteAllBarcodes,
          this, &MainWindow::slotCleanBarcodeList);
  connect(&mTimer, &QTimer::timeout, this, &MainWindow::slotTimerTimeout);
  mTimer.setInterval(1000);
  useSettings(s);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::useSettings(std::shared_ptr<Settings> settings)
{
  if(settings->getAutoFocus())
  {
    mTimer.start();
  }
  else
  {
    mTimer.stop();
  }
  mShowComputerNames = settings->getShowComputerNames();
}

void MainWindow::listBarcode(QVector<std::shared_ptr<Barcode> > barcode)
{
  ui->lwScannedTimes->clear();
  for(auto b : barcode)
  {
    QString itemText = b->getDateTime().toString();
    if(mShowComputerNames)
    {
      itemText += "-" + b->getComputerName();
    }
    QListWidgetItem *item = new QListWidgetItem(itemText);
    item->setData(61, QVariant(b->getId()));
    ui->lwScannedTimes->addItem(item);
  }
  ui->lbCount->setText(QString::number(barcode.size()));
  (barcode.size() != 0)? ui->lbBarcode->setText(
                           barcode[0]->getData()):ui->lbBarcode->setText(
                                                    ui->leBarcode->text());
  ui->leBarcode->setText("");
}

void MainWindow::slotTimerTimeout()
{
  if(this->focusWidget() != ui->leBarcode)
  {
    ui->leBarcode->setFocus();
  }
}

void MainWindow::slotScanButtonClicked()
{
  mIsScan = true;
  ui->pbScan->setEnabled(false);
  ui->pbSearch->setEnabled(true);
}

void MainWindow::slotSearchButtonClicked()
{
  mIsScan = false;
  ui->pbScan->setEnabled(true);
  ui->pbSearch->setEnabled(false);
}

void MainWindow::slotBarcodeEntered()
{
  if(ui->leBarcode->text() != "")
  {
    if(mIsScan)
    {
      emit signalScanBarcode(ui->leBarcode->text());
    }
    slotShowBarcode(ui->leBarcode->text());
  }
}

void MainWindow::slotShowBarcode(const QString &barcode)
{
  listBarcode(emit signalGetBarcode(barcode));
}

void MainWindow::slotBarcodeDeleted(const QString &barcode)
{
  if(ui->lbBarcode->text() == barcode)
  {
    slotCleanBarcodeList();
  }
}

void MainWindow::slotDeleteData()
{
  if(ui->lwScannedTimes->selectedItems().count() == 0)
  {
    return;
  }
  int selectedId = ui->lwScannedTimes->currentItem()->data(61).toInt();
  QMessageBox::StandardButton reply = QMessageBox::question(
        this, tr("Are You Sure?"),
        tr("Are you sure to delete this data?"),
        QMessageBox::Yes|QMessageBox::No);
  if(reply == QMessageBox::Yes)
  {
    emit signalDeleteData(selectedId);
    slotShowBarcode(ui->lbBarcode->text());
  }
}

void MainWindow::slotSettingsChanged(std::shared_ptr<Settings> settings)
{
  useSettings(settings);
}

void MainWindow::slotCleanBarcodeList()
{
  ui->leBarcode->setText("-"); //when deleted barcode, it shows on lbBarcode
  QVector<std::shared_ptr<Barcode>> barcode;
  listBarcode(barcode);
}
