#ifndef DOWNLOADCENTER_H
#define DOWNLOADCENTER_H
#include <QDialog>
#include <QListWidget>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
struct DownloadItem {
    QString filename;
    QString url;
    qint64 received;
    qint64 total;
    int progress;
    QString speed;
    bool active;
    bool paused;
    QString error;
    QListWidgetItem *item;
    QProgressBar *progressBar;
    QLabel *infoLabel;
    QPushButton *pauseBtn;
    QPushButton *cancelBtn;
};
class DownloadCenter : public QDialog {
    Q_OBJECT
public:
    explicit DownloadCenter(QWidget *parent = nullptr);
    ~DownloadCenter();
    void addDownload(const QString &url, const QString &filename);
private slots:
    void updateProgress();
    void pauseDownload(int index);
    void cancelDownload(int index);
    void retryDownload(int index);
    void openFile(int index);
private:
    QListWidget *listWidget;
    QTimer *updateTimer;
    QList<DownloadItem> downloads;
    void updateUI();
    QString formatSize(qint64 bytes);
    QString formatSpeed(qint64 bytesPerSec);
};
#endif
