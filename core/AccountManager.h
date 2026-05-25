#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H
#include <QString>
#include <QList>
#include <QJsonObject>
#include <QDateTime>
#include <QImage>
struct Account {
    QString username;
    QString passwordHash;
    QString avatarPath;
    QDateTime created;
    QJsonObject toJson() const;
    static Account fromJson(const QJsonObject &obj);
};
class AccountManager {
public:
    static bool createAccount(const QString &username, const QString &password, const QString &avatarPath);
    static bool verifyAccount(const QString &username, const QString &password);
    static QList<QString> getAllUsernames();
    static bool deleteAccount(const QString &username);
    static QString getAvatarPath(const QString &username);
    static bool saveAvatar(const QString &username, const QImage &avatar);
    static QString avatarPath();
private:
    static QString accountFilePath(const QString &username);
    static QString hashPassword(const QString &password);
};
#endif
