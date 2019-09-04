/// Settings.hpp
/// \author ohanedan ( oznhndn@gmail.com )

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QObject>

class Settings : public QObject
{
  Q_OBJECT
public:
  Settings(QString lang, bool autoFocus) : mLang(lang), mAutoFocus(autoFocus){}

  inline QString getLang() const
  {
    return mLang;
  }

  inline bool getAutoFocus() const
  {
    return mAutoFocus;
  }

private:
  QString mLang;
  int mAutoFocus;
};

#endif // SETTINGS_HPP
