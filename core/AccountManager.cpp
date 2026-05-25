#include "AccountManager.h"
#include "FileManager.h"
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QDir>
QString AccountManager::hashPassword(const QString &password) {
    return QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
}
bool AccountManager::createAccount(const QString &username, const QString &password, const QString &avatarPath) {
    QJsonObject obj;
    obj["username"] = username;
    obj["passwordHash"] = hashPassword(password);
    obj["avatar"] = avatarPath.isEmpty() ? ":/default_avatar.png" : avatarPath;
    obj["created"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    QJsonDocument doc(obj);
    bool ok = FileManager::saveFile(accountFilePath(username), doc.toJson());
    if (ok && !avatarPath.isEmpty()) {
        QFile::copy(avatarPath, FileManager::getInstallPath() + "/Kinzaki_Creations/yacc1pp.png");
    }
    return ok;
}
bool AccountManager::verifyAccount(const QString &username, const QString &password) {
    QByteArray data = FileManager::loadFile(accountFilePath(username));
    if (data.isEmpty()) return false;
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    return obj["passwordHash"].toString() == hashPassword(password);
}
QList<QString> AccountManager::getAllUsernames() {
    QList<QString> list;
    QDir dir(FileManager::getInstallPath() + "/Kinzaki_Creations/yacc");
    QStringList files = dir.entryList(QStringList() << "*.datafile");
    for (const QString &file : files) list.append(file.left(file.lastIndexOf('.')));
    return list;
}
QString AccountManager::avatarPath() {
    return FileManager::getInstallPath() + "/Kinzaki_Creations/yacc1pp.png";
}
QString AccountManager::accountFilePath(const QString &username) {
    return FileManager::getUserDataPath(username);
}
