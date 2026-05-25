#ifndef HISTORYLOGGER_H
#define HISTORYLOGGER_H
#include <QString>
#include <QDateTime>
class HistoryLogger {
public:
    static void addEntry(const QString &username, const QString &url, const QString &title);
    static QStringList getHistoryForDate(const QString &username, const QDate &date);
};
#endif
