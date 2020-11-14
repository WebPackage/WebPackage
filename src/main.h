#ifndef MAIN_H
#define MAIN_H
#include <QApplication>
#include <qdir.h>
#include <qevent.h>
#include <qfileinfo.h>
#include <qimage.h>
#include <QDir>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonParseError>

#if QT_VERSION >= 0x040000
#include <QTime>
#endif

#include "QFlowView.h"
#if QT_VERSION < 0x040000
#define modifiers state
#define AltModifier AltButton
#define setWindowTitle setCaption
#endif

#if QT_VERSION < 0x030000
#define flush flushX
#endif
void importPkg(QString path);
void exportPkg(QString path);
void start();
void info();
void deletePkg();
void refresh();
#endif // MAIN_H
