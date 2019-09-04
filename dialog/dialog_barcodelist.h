/// dialog_BarcodeList.h
/// \author ohanedan ( oznhndn@gmail.com )

#ifndef BARCODELIST_H
#define BARCODELIST_H

#include <QDialog>
#include "controller.h"

namespace dialog
{
namespace Ui {
class BarcodeList;
}

class BarcodeList : public QDialog
{
  Q_OBJECT

public:
  explicit BarcodeList(Controller *controller);
  ~BarcodeList();

signals:
  void signalShowBarcode(const QString& text);
  QVector<QString>  signalGetAllBarcodeNames();
  void signalDeleteBarcode(const QString& barcode);
  void signalDeleteAllBarcodes();

private slots:
  void slotDeleteSelected();
  void slotReloadList();
  void slotShowBarcode();
  void slotDeleteAllPressed();

private:
  void initList();

private:
  Ui::BarcodeList *ui;
};
}//namespace dialog

#endif // BARCODELIST_H
