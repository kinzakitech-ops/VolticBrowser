#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
class RegisterWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit RegisterWindow(QWidget *parent = nullptr);
private slots:
    void onPasswordChanged(const QString &text);
    void onCreateAccount();
    void onPhantomMode();
private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *confirmEdit;
    QPushButton *createBtn;
    QPushButton *phantomBtn;
    QLabel *confirmLabel;
    bool confirmVisible;
};
#endif
