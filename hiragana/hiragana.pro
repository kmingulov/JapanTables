################################################################################
# HIRAGANA TABLES
################################################################################

# Qt.
QT       += core gui printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Building application.
TARGET = Hiragana
TEMPLATE = app

# Enabling flags.
QMAKE_CXXFLAGS += -std=c++0x

# Sources.
SOURCES += \
    main.cpp \
    WMain.cpp

# Headers.
HEADERS += \
    WMain.h

# Forms.
FORMS += \
    WMain.ui

# Translations.
TRANSLATIONS += \
    lang/default.ts \
    lang/ru_RU.ts
