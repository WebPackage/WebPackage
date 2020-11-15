#ifndef MAIN_H
#define MAIN_H

#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QtGlobal>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QFile>
#include <QDirIterator>

    extern QString id;
    extern QString title;
    extern QString description;
    extern QString author;
    extern QString version;
    extern QString icon;
    extern QString type;
    void generate();

#endif // MAIN_H
