#include "LoginWindow.h"
#include "RegisterWindow.h"
#include "WarningWindow.h"
#include "MainWindow.h"
#include "../core/AccountManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEvent>
#include <QPushButton>
#include <QPixmap>
LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Voltic Browser - Login");
    setFixedSize(900, 600);
    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setAlignment(Qt::AlignCenter);
    QLabel *title = new QLabel("Welcome back,");
    title->setStyleSheet("font-size: 28px;");
    QLabel *sub = new QLabel("Please select your Voltic account to continue using this browser");
    sub->setStyleSheet("color: #aaa;");
    QHBoxLayout *accountsLayout = new QHBoxLayout();
    accountsLayout->setSpacing(30);
    QStringList usernames = AccountManager::getAllUsernames();
    for (const QString &uname : usernames) {
        QWidget *card = new QWidget();
        card->setFixedSize(200, 250);
        card->setStyleSheet("background-color: #2d2d3f; border-radius: 20px;");
        card->setProperty("username", uname);
        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        QLabel *avatar = new QLabel();
        avatar->setFixedSize(100,100);
        avatar->setStyleSheet("border-radius: 50px; background-color: #5a5aff;");
        QPixmap pix(AccountManager::avatarPath());
        if (!pix.isNull()) avatar->setPixmap(pix.scaled(100,100));
        else avatar->setText("?");
        avatar->setAlignment(Qt::AlignCenter);
        QLabel *nameLabel = new QLabel(uname);
        nameLabel->setAlignment(Qt::AlignCenter);
        nameLabel->setStyleSheet("font-size: 16px; color: white;");
        cardLayout->addWidget(avatar, 0, Qt::AlignCenter);
        cardLayout->addWidget(nameLabel);
        accountsLayout->addWidget(card);
        card->installEventFilter(this);
        accounts.append({uname, card, nameLabel, avatar});
    }
    QPushButton *phantomBtn = new QPushButton("Continue as a fantom");
    QPushButton *newProfileBtn = new QPushButton("+ create new profile");
    mainLayout->addWidget(title);
    mainLayout->addWidget(sub);
    mainLayout->addSpacing(40);
    mainLayout->addLayout(accountsLayout);
    mainLayout->addSpacing(40);
    mainLayout->addWidget(phantomBtn);
    mainLayout->addWidget(newProfileBtn);
    setCentralWidget(central);
    connect(phantomBtn, &QPushButton::clicked, this, &LoginWindow::onPhantomMode);
    connect(newProfileBtn, &QPushButton::clicked, this, &LoginWindow::onCreateNewProfile);
}
bool LoginWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Enter) {
        if (QWidget *w = qobject_cast<QWidget*>(obj)) {
            animateBorder(w, true);
        }
    } else if (event->type() == QEvent::Leave) {
        if (QWidget *w = qobject_cast<QWidget*>(obj)) {
            animateBorder(w, false);
        }
    } else if (event->type() == QEvent::MouseButtonPress) {
        if (QWidget *w = qobject_cast<QWidget*>(obj)) {
            QString uname = w->property("username").toString();
            if (!uname.isEmpty()) onAccountSelected(uname);
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
void LoginWindow::animateBorder(QWidget *widget, bool hover) {
    QString color = hover ? "red" : "#2d2d3f";
    widget->setStyleSheet(QString("background-color: %1; border-radius: 20px; border: 2px solid %2;")
                          .arg(hover ? "#3d3d5f" : "#2d2d3f").arg(color));
}
void LoginWindow::onAccountSelected(const QString &username) {
    MainWindow *mainWin = new MainWindow(true, username);
    mainWin->show();
    this->close();
}
void LoginWindow::onCreateNewProfile() {
    RegisterWindow *reg = new RegisterWindow();
    reg->show();
    this->close();
}
void LoginWindow::onPhantomMode() {
    WarningWindow *warn = new WarningWindow(this);
    warn->show();
    this->close();
}
