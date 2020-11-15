#ifndef MAIN_H
#define MAIN_H
#include "browser.h"
#include "flow.h"
#include "QFlowView.h"
#include "webpkg.h"
#include "info.h"
#include "quazip/JlCompress.h"

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

#if QT_VERSION < 0x040000
#define modifiers state
#define AltModifier AltButton
#define setWindowTitle setCaption
#endif

#if QT_VERSION < 0x030000
#define flush flushX
#endif
class main : QObject
{
    Q_OBJECT
public slots:
static void importPkg(QString path);
static void exportPkg(QString path);
static void start();
static void info();
static void deletePkg();
static void refresh();
static void updateTitle();
static void connectStuff();
};


#endif // MAIN_H
