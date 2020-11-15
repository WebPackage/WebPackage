#include "main.h"

QString id;
QString title;
QString description;
QString author;
QString version;
QString icon;
QString type;
void copyDirectoryNested(QString from,QString to)
{

    QDirIterator it(from, QDirIterator::Subdirectories);

    while (it.hasNext()) {

        QString file_in = it.next();

        QFileInfo file_info = QFileInfo(file_in);

        QString file_out = file_in;
        file_out.replace(from,to);

        if(file_info.isFile())
        {
            //is file copy
            QFile::copy(file_in, file_out);
        }

        if(file_info.isDir())
        {
            //dir mkdir
            QDir dir(file_out);
            if (!dir.exists())
                dir.mkpath(".");
        }
    }
}
void generate();
int main(int argc, char *argv[])
{
    QApplication * app = new QApplication(argc, argv);
    QCommandLineParser parser;
    parser.setApplicationDescription("WebPackage Skeleton Generator");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption cliOption(QStringList() << "c" << "cli", "run in headless mode for scripting");
    parser.addOption(cliOption);

    QCommandLineOption idOption(QStringList() << "id", "use <id> as id, defaults to foo", "id");
    parser.addOption(idOption);

    QCommandLineOption titleOption(QStringList() << "title", "use <title> as title, defaults to foo", "title");
    parser.addOption(titleOption);

    QCommandLineOption descriptionOption(QStringList() << "description", "use <description> as description, defaults to foo bar", "description");
    parser.addOption(descriptionOption);

    QCommandLineOption authorOption(QStringList() << "author", "use <author> as author, defaults to John Doe", "author");
    parser.addOption(authorOption);

    QCommandLineOption versionOption(QStringList() << "version", "use <version> as version, defaults to 1.0", "version");
    parser.addOption(versionOption);

    QCommandLineOption iconOption(QStringList() << "icon", "use <icon> as icon, defaults to icon.png", "icon");
    parser.addOption(iconOption);

    QCommandLineOption typeOption(QStringList() << "type", "use <type> as type, defaults to generic", "type");
    parser.addOption(typeOption);

    parser.process(*app);
    bool cli = parser.isSet(cliOption);
    id = (parser.value(idOption) == "")? "foo" : parser.value(idOption);
    title = (parser.value(titleOption) == "")? "bar" : parser.value(titleOption);
    description = (parser.value(descriptionOption) == "")? "foo bar" : parser.value(descriptionOption);
    author = (parser.value(authorOption) == "")? "John Doe" : parser.value(authorOption);
    version = (parser.value(versionOption) == "")? "1.0" : parser.value(versionOption);
    icon = (parser.value(iconOption) == "")? "icon.png" : parser.value(iconOption);
    type = (parser.value(typeOption) == "")? "generic" : parser.value(typeOption);
    if (cli)
    {
        generate();
        app->exit(0);
        return 0;
    }
    else
    {
        MainWindow * win = new MainWindow;
        win->setWindowIcon(QIcon(":/images/icon/webpkg-gen.png"));
        win->show();
    }

    int result = app->exec();
    return result;
}

void generate()
{
    QJsonObject metaObject;
    metaObject.insert("id", QJsonValue::fromVariant(id));
    metaObject.insert("title", QJsonValue::fromVariant(title));
    metaObject.insert("description", QJsonValue::fromVariant(description));
    metaObject.insert("author", QJsonValue::fromVariant(author));
    metaObject.insert("version", QJsonValue::fromVariant(version));
    metaObject.insert("icon", QJsonValue::fromVariant(icon));
    metaObject.insert("type", QJsonValue::fromVariant(type));
    QJsonDocument meta(metaObject);
    if (!QDir(QDir::homePath() + "/.webpkg").exists())
        QDir().mkdir(QDir::homePath() + "/.webpkg");
    QDir rootDir = QDir(QDir::homePath() + "/.webpkg");
    if (!QDir(rootDir.path() + "/" + id + ".web").exists())
        QDir().mkdir(rootDir.path() + "/" + id + ".web");
    QDir packageDir = QDir(rootDir.path() + "/" + id + ".web");
    if (!QDir(packageDir.path() + "/meta").exists())
        QDir().mkdir(packageDir.path() + "/meta");
    QDir metaDir = QDir(packageDir.path() + "/meta");
    if (!QDir(packageDir.path() + "/app").exists())
        QDir().mkdir(packageDir.path() + "/app");
    QDir appDir = QDir(packageDir.path() + "/app");
    QFile packageJson(metaDir.path() + "/package.json");
    packageJson.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    packageJson.write(meta.toJson());
    packageJson.close();
    copyDirectoryNested(":/resources/meta", metaDir.path());
    QFile packageIcon(metaDir.path() + "/icon.png");
    packageIcon.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    packageIcon.rename(icon);
    packageIcon.close();

}
