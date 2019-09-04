/// MainWindow.h
/// \author ohanedan ( oznhndn@gmail.com )

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <memory>
#include "controller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(Controller *controller, std::shared_ptr<Settings> s);
  ~MainWindow();

private:
  void useSettings(std::shared_ptr<Settings> settings);
  void listBarcode(QVector<std::shared_ptr<Barcode>> barcode);

signals:
  void signalDeleteData(int id);
  void signalScanBarcode(const QString& barcode);
  QVector<std::shared_ptr<Barcode>> signalGetBarcode(const QString& barcode);

private slots:
  void slotTimerTimeout();
  void slotScanButtonClicked();
  void slotSearchButtonClicked();
  void slotBarcodeEntered();
  void slotShowBarcode(const QString& barcode);
  void slotBarcodeDeleted(const QString &barcode);
  void slotDeleteData();
  void slotSettingsChanged(std::shared_ptr<Settings> settings);
  void slotCleanBarcodeList();

private:
  Ui::MainWindow *ui;
  QTimer mTimer;
  bool mIsScan;
  bool mShowComputerNames;
};

#endif // MAINWINDOW_H
