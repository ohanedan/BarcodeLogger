#include <QApplication>
#include <QTranslator>
#include <memory>
#include "mainwindow.h"
#include "settings.hpp"
#include "controller.h"
#include "database.h"

void initLanguage(const QString& lang)
{
  QTranslator *translator = new QTranslator();
  if(lang != "en")
  {
    translator->load(":/languages/" + lang + ".qm");
    qApp->installTranslator(translator);
  }
  else
  {
    delete translator;
  }
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ISaver *saver = new Database();
  Controller controller(saver);
  std::shared_ptr<Settings> settings = saver->getSettings();
  initLanguage(settings->getLang());
  MainWindow w(&controller, settings);
  w.show();

  return a.exec();
}

