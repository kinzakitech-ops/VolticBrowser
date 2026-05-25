#ifndef WARNINGWINDOW_H
#define WARNINGWINDOW_H
#include <QMainWindow>
class WarningWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit WarningWindow(QWidget *parent = nullptr);
private slots:
    void onContinue();
};
#endif
