#include "HistoryLogger.h"
#include "FileManager.h"
#include <QTextStream>
void HistoryLogger::addEntry(const QString &username, const QString &url, const QString &title) {
    QDate today = QDate::currentDate();
    QString histPath = FileManager::getHistoryPath(username, today);
    QFile file(histPath);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString(Qt::ISODate) << " | " << title << " | " << url << "\n";
    }
}
QStringList HistoryLogger::getHistoryForDate(const QString &username, const QDate &date) {
    QString histPath = FileManager::getHistoryPath(username, date);
    QFile file(histPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return QStringList();
    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) lines << in.readLine();
    return lines;
}
