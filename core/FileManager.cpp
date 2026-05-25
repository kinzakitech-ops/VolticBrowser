#include "FileManager.h"
#include <QStandardPaths>
#include <QDebug>
QString FileManager::s_installPath = "";
bool FileManager::initializeInstallPath(const QString &installPath) {
    s_installPath = installPath;
    return ensureDirectoriesExist();
}
QString FileManager::getInstallPath() {
    if (s_installPath.isEmpty()) {
        s_installPath = QCoreApplication::applicationDirPath();
        ensureDirectoriesExist();
    }
    return s_installPath;
}
bool FileManager::ensureDirectoriesExist() {
    QDir dir(s_installPath);
    if (!dir.exists("Kinzaki_Creations")) dir.mkdir("Kinzaki_Creations");
    dir.cd("Kinzaki_Creations");
    if (!dir.exists("yacc")) dir.mkdir("yacc");
    if (!dir.exists("Hist")) dir.mkdir("Hist");
    if (!dir.exists("Downloads")) dir.mkdir("Downloads");
    return true;
}
QString FileManager::getUserDataPath(const QString &username) {
    return QString("%1/Kinzaki_Creations/yacc/%2.datafile").arg(s_installPath).arg(username);
}
QString FileManager::getHistoryPath(const QString &username, const QDate &date) {
    QString path = QString("%1/Kinzaki_Creations/Hist/%2/%3/").arg(s_installPath).arg(username).arg(date.toString("yyyy.MM.dd"));
    QDir().mkpath(path);
    return path + "site.hist";
}
bool FileManager::saveFile(const QString &path, const QByteArray &data) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) return false;
    file.write(data);
    return true;
}
QByteArray FileManager::loadFile(const QString &path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return QByteArray();
    return file.readAll();
}
