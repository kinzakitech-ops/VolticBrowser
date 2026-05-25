#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QString>
#include <QDir>
#include <QCoreApplication>
class FileManager {
public:
    static bool initializeInstallPath(const QString &installPath);
    static QString getInstallPath();
    static bool ensureDirectoriesExist();
    static QString getUserDataPath(const QString &username);
    static QString getHistoryPath(const QString &username, const QDate &date);
    static bool saveFile(const QString &path, const QByteArray &data);
    static QByteArray loadFile(const QString &path);
private:
    static QString s_installPath;
};
#endif
