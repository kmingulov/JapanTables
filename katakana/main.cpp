#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QLocale>

#include "WMain.h"

int main(int argc, char *argv[])
{
    // Running application.
    QApplication a(argc, argv);

    // Loading translation.
    QTranslator translator;
    translator.load("katakana_" + QLocale::system().name() + ".qm");
    a.installTranslator(&translator);

    // Showing window.
    WMain w;
    w.show();

    return a.exec();
}
