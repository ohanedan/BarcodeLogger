/// dialog_Settings.h
/// \author ohanedan ( oznhndn@gmail.com )

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <memory>
#include "controller.h"
#include "settings.hpp"

namespace dialog
{
namespace Ui {
class Settings;
}

class Settings : public QDialog
{
  Q_OBJECT

public:
  explicit Settings(Controller *controller);
  ~Settings();

private:
  void init();

signals:
  std::shared_ptr<::Settings> signalGetSettings();
  void signalSetSettings(std::shared_ptr<::Settings> settings);

private slots:
  void slotSaveData();

private:
  Ui::Settings *ui;
  std::shared_ptr<::Settings> mSettings;
};
}//namespace dialog

#endif // SETTINGSDIALOG_H
