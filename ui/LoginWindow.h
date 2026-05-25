#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QList>
#include <QPropertyAnimation>
struct AccountItem {
    QString username;
    QWidget *card;
    QLabel *nameLabel;
    QLabel *avatarLabel;
};
class LoginWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
private slots:
    void onAccountSelected(const QString &username);
    void onCreateNewProfile();
    void onPhantomMode();
private:
    QList<AccountItem> accounts;
    void animateBorder(QWidget *widget, bool hover);
};
#endif
