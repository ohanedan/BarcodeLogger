/// dialog_About.h
/// \author ohanedan ( oznhndn@gmail.com )

#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace dialog
{
namespace Ui {
class About;
}

class About : public QDialog
{
  Q_OBJECT

public:
  explicit About(QWidget *parent = nullptr);
  ~About();

private:
  Ui::About *ui;
};
}//namespace dialog

#endif // ABOUT_H
