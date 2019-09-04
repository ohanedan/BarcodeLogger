/// Settings.hpp
/// \author ohanedan ( oznhndn@gmail.com )

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QObject>

class Settings : public QObject
{
  Q_OBJECT
public:
  Settings(QString lang, bool autoFocus, bool showComputerNames) : mLang(lang),
    mAutoFocus(autoFocus), mShowComputerNames(showComputerNames){}

  inline QString getLang() const
  {
    return mLang;
  }

  inline bool getAutoFocus() const
  {
    return mAutoFocus;
  }

  inline bool getShowComputerNames() const
  {
    return mShowComputerNames;
  }

private:
  QString mLang;
  int mAutoFocus;
  int mShowComputerNames;
};

#endif // SETTINGS_HPP
