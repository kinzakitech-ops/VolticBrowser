#include "DownloadCenter.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFileInfo>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include "../core/FileManager.h"
DownloadCenter::DownloadCenter(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Download Center - Voltic Browser");
    setFixedSize(700, 500);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    listWidget = new QListWidget();
    listWidget->setStyleSheet("QListWidget::item { padding: 10px; border-bottom: 1px solid #3d3d5f; }");
    mainLayout->addWidget(listWidget);
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &DownloadCenter::updateProgress);
    updateTimer->start(500);
}
DownloadCenter::~DownloadCenter() {
    updateTimer->stop();
}
void DownloadCenter::addDownload(const QString &url, const QString &filename) {
    DownloadItem item;
    item.filename = filename;
    item.url = url;
    item.received = 0;
    item.total = 0;
    item.progress = 0;
    item.speed = "0 KB/s";
    item.active = true;
    item.paused = false;
    item.error = "";
    QListWidgetItem *listItem = new QListWidgetItem(listWidget);
    listWidget->addItem(listItem);
    item.item = listItem;
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);
    QVBoxLayout *textLayout = new QVBoxLayout();
    QLabel *nameLabel = new QLabel(filename);
    nameLabel->setStyleSheet("font-weight: bold;");
    item.infoLabel = new QLabel("Starting...");
    item.progressBar = new QProgressBar();
    item.progressBar->setRange(0, 100);
    textLayout->addWidget(nameLabel);
    textLayout->addWidget(item.infoLabel);
    textLayout->addWidget(item.progressBar);
    layout->addLayout(textLayout);
    item.pauseBtn = new QPushButton("⏸");
    item.cancelBtn = new QPushButton("✕");
    layout->addWidget(item.pauseBtn);
    layout->addWidget(item.cancelBtn);
    widget->setLayout(layout);
    listWidget->setItemWidget(listItem, widget);
    connect(item.pauseBtn, &QPushButton::clicked, [this, index = downloads.size()]() { pauseDownload(index); });
    connect(item.cancelBtn, &QPushButton::clicked, [this, index = downloads.size()]() { cancelDownload(index); });
    downloads.append(item);
    listWidget->setFixedHeight(listWidget->sizeHintForRow(0) * downloads.size() + 10);
}
void DownloadCenter::updateProgress() {
    updateUI();
}
void DownloadCenter::updateUI() {
    for (int i = 0; i < downloads.size(); ++i) {
        DownloadItem &item = downloads[i];
        if (item.active && !item.paused) {
            static int counter = 0;
            counter++;
            item.received += 1024 * (counter % 10);
            if (item.received > item.total && item.total > 0) item.received = item.total;
            if (item.total == 0) item.total = 1024 * 1024 * 5;
            item.progress = (int)((double)item.received / item.total * 100);
            item.speed = QString("%1 KB/s").arg((counter % 50) + 50);
            item.infoLabel->setText(QString("%1 / %2 - %3").arg(formatSize(item.received)).arg(formatSize(item.total)).arg(item.speed));
            item.progressBar->setValue(item.progress);
            if (item.progress >= 100) {
                item.active = false;
                item.infoLabel->setText("Completed - " + formatSize(item.total));
                item.pauseBtn->setEnabled(false);
                QPushButton *openBtn = new QPushButton("✓");
                connect(openBtn, &QPushButton::clicked, [this, i]() { openFile(i); });
                QWidget *widget = listWidget->itemWidget(item.item);
                QHBoxLayout *layout = qobject_cast<QHBoxLayout*>(widget->layout());
                layout->addWidget(openBtn);
                item.pauseBtn->deleteLater();
                item.cancelBtn->deleteLater();
            }
        } else if (!item.active && item.error.isEmpty() && item.progress < 100) {
            item.error = "Err connection lost : internet turned off";
            item.infoLabel->setText("Failed: " + item.error);
            QPushButton *retryBtn = new QPushButton("↻");
            connect(retryBtn, &QPushButton::clicked, [this, i]() { retryDownload(i); });
            QWidget *widget = listWidget->itemWidget(item.item);
            QHBoxLayout *layout = qobject_cast<QHBoxLayout*>(widget->layout());
            layout->addWidget(retryBtn);
        }
    }
}
void DownloadCenter::pauseDownload(int index) {
    if (index >= 0 && index < downloads.size()) {
        downloads[index].paused = !downloads[index].paused;
        downloads[index].infoLabel->setText(downloads[index].paused ? "Paused" : "Resumed");
        downloads[index].pauseBtn->setText(downloads[index].paused ? "▶" : "⏸");
    }
}
void DownloadCenter::cancelDownload(int index) {
    if (index >= 0 && index < downloads.size()) {
        downloads[index].active = false;
        downloads[index].error = "User Stop it";
        downloads[index].infoLabel->setText("Cancelled by user");
        downloads[index].pauseBtn->setEnabled(false);
        downloads[index].cancelBtn->setEnabled(false);
    }
}
void DownloadCenter::retryDownload(int index) {
    if (index >= 0 && index < downloads.size()) {
        downloads[index].received = 0;
        downloads[index].progress = 0;
        downloads[index].active = true;
        downloads[index].error = "";
        downloads[index].infoLabel->setText("Retrying...");
    }
}
void DownloadCenter::openFile(int index) {
    if (index >= 0 && index < downloads.size()) {
        QString path = FileManager::getInstallPath() + "/Kinzaki_Creations/Downloads/" + downloads[index].filename;
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    }
}
QString DownloadCenter::formatSize(qint64 bytes) {
    if (bytes < 1024) return QString("%1 B").arg(bytes);
    if (bytes < 1024 * 1024) return QString("%1 KB").arg(bytes / 1024);
    return QString("%1 MB").arg(bytes / (1024 * 1024));
}
QString DownloadCenter::formatSpeed(qint64 bytesPerSec) {
    return formatSize(bytesPerSec) + "/s";
}
