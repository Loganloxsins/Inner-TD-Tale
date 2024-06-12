#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "include/map/map.h"
#include <QDebug>
#include <QString>

int main(int argc, char *argv[]) {



    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Inner-TD-Tale_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;

    w.show();

    return a.exec();
}
