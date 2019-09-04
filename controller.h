/// Controller.h
/// \author ohanedan ( oznhndn@gmail.com )

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "isaver.h"

class Controller : public QObject
{
  Q_OBJECT
public:
  Controller(ISaver *saver);

private:
  void initSaver(ISaver *saver);

signals:
  void signalScanBarcode(const QString& barcode);
  QVector<std::shared_ptr<Barcode>> signalGetBarcode(const QString& barcode);
  QVector<QString> signalGetAllBarcodeNames();
  void signalShowBarcode(const QString& text);
  void signalDeleteBarcode(const QString& barcode);
  void signalDeleteAllBarcodes();
  void signalDeleteData(int id);
  std::shared_ptr<Settings> signalGetSettings();
  void signalSetSettings(std::shared_ptr<Settings> settings);

public slots:
  void slotListAllBarcodes();
  void slotShowAbout();
  void slotShowSettings();
};

#endif // CONTROLLER_H
