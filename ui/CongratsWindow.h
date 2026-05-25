#ifndef CONGRATSWINDOW_H
#define CONGRATSWINDOW_H
#include <QMainWindow>
#include <QTimer>
class CongratsWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit CongratsWindow(const QString &username, QWidget *parent = nullptr);
private slots:
    void onTimeout();
private:
    QTimer *timer;
};
#endif
