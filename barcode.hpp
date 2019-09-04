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
          QDateTime dateTime) : mId(id), mData(data), mDateTime(dateTime){}

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

private:
  int mId;
  QString mData;
  QDateTime mDateTime;
};

#endif // BARCODE_HPP
