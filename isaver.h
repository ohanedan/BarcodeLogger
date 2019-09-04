/// ISaver.h
/// \author ohanedan ( oznhndn@gmail.com )

#ifndef ISAVER_H
#define ISAVER_H

#include <QObject>
#include <memory>
#include "barcode.hpp"
#include "settings.hpp"

class ISaver : public QObject
{
  Q_OBJECT
public:
  ISaver();
  virtual ~ISaver();
  virtual std::shared_ptr<Settings> getSettings() = 0;
  virtual QString init() = 0;

public slots:
  virtual QVector<std::shared_ptr<Barcode>> slotGetBarcode(
      const QString& barcodeData) = 0;
  virtual void slotSaveBarcode(const QString& barcodeData) = 0;
  virtual QVector<QString> slotGetAllBarcodeNames() = 0;
  virtual void slotDeleteBarcode(const QString& barcode) = 0;
  virtual void slotDeleteData(int id) = 0;
  virtual void slotSetSettings(std::shared_ptr<Settings> settings) = 0;
  virtual std::shared_ptr<Settings> slotGetSettings() = 0;
  virtual void slotDeleteAllBarcodes() = 0;
};

#endif // ISAVER_H
