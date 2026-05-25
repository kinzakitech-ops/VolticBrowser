#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(bool loggedIn, const QString &username = "", QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onGoClicked();
    void onUrlReturn();

private:
    QLineEdit *urlBar;
    QPushButton *goBtn;
    QString currentUsername;
    bool isLoggedMode;
    
    void loadUrl(const QString &url);
};
#endif
