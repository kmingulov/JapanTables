#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QLocale>

#include "WMain.h"

int main(int argc, char *argv[])
{
    // Running application.
    QApplication a(argc, argv);

    // Loading UTF-8 codec.
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    // Loading translation.
    QTranslator translator;
    translator.load(QLocale::system().name(), "lang/");
    a.installTranslator(&translator);

    // Showing window.
    WMain w;
    w.show();

    return a.exec();
}
