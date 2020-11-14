#include "browser.h"
#include "flow.h"
#include "QFlowView.h"
#include "webpkg.h"
#include "main.h"
#include "info.h"
#include "quazip/JlCompress.h"
QList<Package> packages;
int argc = 0;
char **argv;
QApplication * a = new QApplication(argc, argv);
Browser * b = new Browser;
Flow * f = new Flow;
QFlowView * flowView = f->findChild<QFlowView*>("flowView");
QWebEngineView * webView = b->findChild<QWebEngineView*>("webView");
bool copyPath(QString sourceDir, QString destinationDir, bool overWriteDirectory)
{
    QDir originDirectory(sourceDir);

    if (! originDirectory.exists())
    {
        return false;
    }

    QDir destinationDirectory(destinationDir);

    if(destinationDirectory.exists() && !overWriteDirectory)
    {
        return false;
    }
    else if(destinationDirectory.exists() && overWriteDirectory)
    {
        destinationDirectory.removeRecursively();
    }

    originDirectory.mkpath(destinationDir);

    foreach (QString directoryName, originDirectory.entryList(QDir::Dirs | \
                                                              QDir::NoDotAndDotDot))
    {
        QString destinationPath = destinationDir + "/" + directoryName;
        originDirectory.mkpath(destinationPath);
        copyPath(sourceDir + "/" + directoryName, destinationPath, overWriteDirectory);
    }

    foreach (QString fileName, originDirectory.entryList(QDir::Files))
    {
        QFile::copy(sourceDir + "/" + fileName, destinationDir + "/" + fileName);
    }

    /*! Possible race-condition mitigation? */
    QDir finalDestination(destinationDir);
    finalDestination.refresh();

    if(finalDestination.exists())
    {
        return true;
    }

    return false;
}
void initialize()
{
    if (!QDir(QDir::homePath() + "/.webpkg").exists())
        QDir().mkdir(QDir::homePath() + "/.webpkg");
    flowView->setSlideSize(QSize(256, 256));
    QDir root = QDir(QDir::homePath() + "/.webpkg");
    root.setFilter(QDir::Dirs| QDir::NoDotAndDotDot | QDir::NoSymLinks);

    qDebug() << "Scanning: " << root.path();

    QStringList pakList = root.entryList();
    for (QString pak : pakList)
    {
        QDir package = QDir(root.path() + "/" + pak + "/meta/");
        package.setNameFilters(QStringList("*.json"));
        package.setFilter(QDir::Files | QDir::NoSymLinks);
        QStringList metaList = package.entryList();
        for (QString meta : metaList)
        {

            if(package.path() + "/" + meta == package.path() + "/package.json")
            {
                qDebug() << "Found package manifest: " << package.path() + "/" + meta;
                Package pak;
                QImage img;
                QFile file;
                file.setFileName(package.path() + "/package.json");
                file.open(QIODevice::ReadOnly | QIODevice::Text);
                QJsonParseError jsonError;
                QJsonDocument flowerJson = QJsonDocument::fromJson(file.readAll(),&jsonError);
                if (jsonError.error != QJsonParseError::NoError){
                qDebug() << jsonError.errorString();
                }
                QMap<QString, QVariant> map = flowerJson.toVariant().toMap();
                QString iconPath = package.path() + "/" + map["icon"].toString();
                img.load(iconPath);
                pak.id = map["id"].toString();
                pak.title = map["title"].toString();
                pak.description = map["description"].toString();
                pak.author = map["author"].toString();
                pak.version = map["version"].toString();
                pak.icon = map["icon"].toString();
                pak.type = map["type"].toString();
                flowView->addSlide(img, pak);
                packages.append(pak);
            }
        }
    }
    flowView->setCenterIndex(flowView->slideCount()/2);

    flowView->setBackgroundColor(Qt::black);
}

void importPkg(QString path)
{
  QFileInfo archive;
  archive.setFile(path);
  if (archive.exists())
  {
      QImage img;
      Package pak;
      QString unpackedPath = JlCompress::extractDir(path, QDir::homePath() + "/.webpkg").front();
      QFile file;
      file.setFileName(unpackedPath + "meta/package.json");
      file.open(QIODevice::ReadOnly | QIODevice::Text);
      QJsonParseError jsonError;
      QJsonDocument flowerJson = QJsonDocument::fromJson(file.readAll(),&jsonError);
      if (jsonError.error != QJsonParseError::NoError){
      qDebug() << jsonError.errorString();
      }
      QMap<QString, QVariant> map = flowerJson.toVariant().toMap();
      QString iconPath = unpackedPath + "meta/" + map["icon"].toString();
      img.load(iconPath);
      pak.id = map["id"].toString();
      pak.title = map["title"].toString();
      pak.description = map["description"].toString();
      pak.author = map["author"].toString();
      pak.version = map["version"].toString();
      pak.icon = map["icon"].toString();
      pak.type = map["type"].toString();
      flowView->addSlide(img, pak);
      packages.append(pak);
      flowView->setCenterIndex(flowView->slideCount()/2);
  }
}
void exportPkg(QString path)
{
    QFileInfo archive;
    archive.setFile(path);
    if (archive.dir().exists())
    {
        Package pak = flowView->getCurrentPackage();
        QTemporaryDir temp;
        copyPath(QDir::homePath() + "/.webpkg/" + pak.id + ".web", temp.path() + "/" + pak.id + ".web", true);
        JlCompress::compressDir(archive.absoluteFilePath(), temp.path());
        temp.remove();
    }
}
void start()
{
    Package pak = flowView->getCurrentPackage();
    webView->setUrl(QUrl(QString("file://" + QDir::homePath() + "/.webpkg/" + pak.id + ".web/app/index.html")));
    b->showFullScreen();
}
void info()
{
    Package pak = flowView->getCurrentPackage();
    Info * i = new Info;
    QTextBrowser * textBrowser = i->findChild<QTextBrowser*>("textBrowser");
    textBrowser->insertPlainText("Title: " + pak.title +
                                 "\nDescription: " + pak.description +
                                 "\nAuthor: " + pak.author +
                                 "\nVersion: " + pak.version);
    i->show();

}
void deletePkg()
{
    Package pak = flowView->getCurrentPackage();
    QDir(QDir::homePath() + "/.webpkg/" + pak.id + ".web").removeRecursively();
    packages.clear();
    flowView->clear();
    initialize();
}
void refresh()
{
    packages.clear();
    flowView->clear();
    initialize();
}
int main()
{
  initialize();

  f->show();

  a->connect( a, SIGNAL(lastWindowClosed()), a, SLOT(quit()) );
  int result = a->exec();

  delete flowView;
  delete webView;
  delete b;
  delete f;
  delete a;

  return result;
}
