#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QHostInfo>
#include "database.h"

Database::Database() : ISaver()
{}

QString Database::init()
{
  mDb = QSqlDatabase::addDatabase("QSQLITE");
  mDb.setDatabaseName("database.db");
  if (!mDb.open()) {
    return tr("Database Connection Error");
  }
  else if(mDb.tables().count() == 0)
  {
    createTables();
    return tr("Database is empty, created database.");
  }
  return nullptr;
}

void Database::createTables()
{
  mDb.exec("CREATE TABLE \"barcodes\" ("
           "\"id\"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
           "\"data\"	TEXT NOT NULL,"
           "\"computer\"	TEXT NOT NULL,"
           "\"datetime\"	TEXT NOT NULL);");
  mDb.exec("CREATE TABLE \"settings\" ("
           "\"lang\"	TEXT NOT NULL,"
           "\"showComputerNames\"	INTEGER NOT NULL,"
           "\"autofocus\"	INTEGER NOT NULL);");
  mDb.exec("INSERT INTO settings VALUES(\"en\",1,1)");
}

QVector<std::shared_ptr<Barcode>> Database::slotGetBarcode(
    const QString &barcodeData)
{
  QVector<std::shared_ptr<Barcode>> temp;
  QSqlQuery query = mDb.exec("SELECT * FROM barcodes WHERE data="
                             "\"" + barcodeData + "\"");
  while(query.next())
  {
    temp.append(std::make_shared<Barcode>(query.value("id").toInt(),
                                          query.value("data").toString(),
                                          QDateTime::fromTime_t(
                                            query.value("datetime").toUInt()),
                                          query.value("computer").toString()));
  }
  return temp;
}

std::shared_ptr<Settings> Database::getSettings()
{
  QSqlQuery query = mDb.exec("SELECT * FROM settings");
  query.next();
  return std::make_shared<Settings>(query.value("lang").toString(),
                                    query.value("autofocus").toBool(),
                                    query.value("showComputerNames").toBool());
}

void Database::slotSetSettings(std::shared_ptr<Settings> settings)
{
  mDb.exec("UPDATE settings SET lang=\"" + settings->getLang() + "\""
           + ", autofocus=" + QString::number(settings->getAutoFocus()) +
           ", showComputerNames=" + QString::number(
             settings->getShowComputerNames()));
}

std::shared_ptr<Settings> Database::slotGetSettings()
{
  return getSettings();
}

void Database::slotDeleteAllBarcodes()
{
  mDb.exec("DELETE FROM barcodes");
}

void Database::slotSaveBarcode(const QString& barcodeData)
{
  QString time = QString::number(QDateTime::currentDateTime().toTime_t());
  mDb.exec("INSERT INTO barcodes(data,datetime,computer) VALUES('" + barcodeData
           + "', " + time + ",'" + QHostInfo::localHostName() + "');");
}

QVector<QString> Database::slotGetAllBarcodeNames()
{
  QVector<QString> temp;
  QSqlQuery query = mDb.exec("SELECT DISTINCT data FROM barcodes");
  while(query.next())
  {
    temp.append(query.value("data").toString());
  }
  return temp;
}

void Database::slotDeleteBarcode(const QString &barcode)
{
  mDb.exec("DELETE FROM barcodes WHERE data=\"" + barcode + "\"");
}

void Database::slotDeleteData(int id)
{
  mDb.exec("DELETE FROM barcodes WHERE id=" + QString::number(id));
}
