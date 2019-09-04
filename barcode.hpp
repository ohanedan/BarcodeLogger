/// Barcode.hpp
/// \author ohanedan ( oznhndn@gmail.com )

#ifndef BARCODE_HPP
#define BARCODE_HPP

#include <QObject>
#include <QDateTime>

class Barcode : public QObject
{
  Q_OBJECT
public:
  Barcode(int id, QString data,
          QDateTime dateTime, QString computerName) : mId(id), mData(data),
    mComputerName(computerName), mDateTime(dateTime){}

  inline int getId() const
  {
    return mId;
  }

  inline QString getData()  const
  {
   return mData;
  }

  inline QDateTime getDateTime() const
  {
    return mDateTime;
  }

  inline QString getComputerName() const
  {
    return mComputerName;
  }

private:
  int mId;
  QString mData;
  QString mComputerName;
  QDateTime mDateTime;
};

#endif // BARCODE_HPP
