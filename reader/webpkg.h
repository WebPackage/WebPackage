#ifndef WEBPKG_H
#define WEBPKG_H

#include <QApplication>
typedef struct WebPkg
{
    QString id;
    QString title;
    QString description;
    QString author;
    QString version;
    QString icon;
    QString type;
} Package;

#endif // WEBPKG_H
