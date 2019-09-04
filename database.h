/// Database.h
/// \author ohanedan ( oznhndn@gmail.com )

#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include "isaver.h"

class Database : public ISaver
{
  Q_OBJECT
public:
  Database();
  std::shared_ptr<Settings> getSettings();
  QString init();

private:
  void createTables();

public slots:
  QVector<std::shared_ptr<Barcode>> slotGetBarcode(const QString& barcodeData);
  void slotSaveBarcode(const QString& barcodeData);
  QVector<QString> slotGetAllBarcodeNames();
  void slotDeleteBarcode(const QString& barcode);
  void slotDeleteData(int id);
  void slotSetSettings(std::shared_ptr<Settings> settings);
  std::shared_ptr<Settings> slotGetSettings();
  void slotDeleteAllBarcodes();

private:
  QSqlDatabase mDb;
};

#endif // DATABASE_H
