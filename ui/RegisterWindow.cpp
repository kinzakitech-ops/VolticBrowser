#include "RegisterWindow.h"
#include "CongratsWindow.h"
#include "WarningWindow.h"
#include "../core/AccountManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QImage>
RegisterWindow::RegisterWindow(QWidget *parent) : QMainWindow(parent), confirmVisible(false) {
    setWindowTitle("Voltic Browser - Create Account");
    setFixedSize(550, 650);
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setAlignment(Qt::AlignCenter);
    QLabel *title = new QLabel("Welcome to Voltic Browser");
    title->setStyleSheet("font-size: 28px; font-weight: bold; color: #5a5aff;");
    title->setAlignment(Qt::AlignCenter);
    QLabel *subtitle = new QLabel("select your avatar :");
    subtitle->setStyleSheet("font-size: 14px; color: #aaa;");
    QPushButton *avatarBtn = new QPushButton("Choose Avatar");
    avatarBtn->setFixedWidth(200);
    usernameEdit = new QLineEdit();
    usernameEdit->setPlaceholderText("Username (required)");
    usernameEdit->setMinimumHeight(40);
    passwordEdit = new QLineEdit();
    passwordEdit->setPlaceholderText("Password (optional)");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setMinimumHeight(40);
    confirmLabel = new QLabel("Confirm Password:");
    confirmEdit = new QLineEdit();
    confirmEdit->setEchoMode(QLineEdit::Password);
    confirmEdit->setVisible(false);
    confirmLabel->setVisible(false);
    createBtn = new QPushButton("Create my account");
    createBtn->setStyleSheet("background-color: #5a5aff; color: white; padding: 12px; border-radius: 12px;");
    phantomBtn = new QPushButton("Continue as Phantom");
    phantomBtn->setStyleSheet("background-color: transparent; border: 1px solid #5a5aff; padding: 12px; border-radius: 12px;");
    layout->addWidget(title);
    layout->addSpacing(20);
    layout->addWidget(subtitle);
    layout->addSpacing(20);
    layout->addWidget(avatarBtn);
    layout->addSpacing(20);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(confirmLabel);
    layout->addWidget(confirmEdit);
    layout->addSpacing(30);
    layout->addWidget(createBtn);
    layout->addWidget(phantomBtn);
    setCentralWidget(central);
    connect(passwordEdit, &QLineEdit::textChanged, this, &RegisterWindow::onPasswordChanged);
    connect(createBtn, &QPushButton::clicked, this, &RegisterWindow::onCreateAccount);
    connect(phantomBtn, &QPushButton::clicked, this, &RegisterWindow::onPhantomMode);
    connect(avatarBtn, &QPushButton::clicked, [this](){
        QString fileName = QFileDialog::getOpenFileName(this, "Select Avatar", "", "Images (*.png *.jpg)");
        if (!fileName.isEmpty()) {
            QImage img(fileName);
            img.scaled(100,100, Qt::KeepAspectRatio);
            img.save(AccountManager::avatarPath());
        }
    });
}
void RegisterWindow::onPasswordChanged(const QString &text) {
    bool hasText = !text.isEmpty();
    if (hasText != confirmVisible) {
        confirmVisible = hasText;
        confirmEdit->setVisible(hasText);
        confirmLabel->setVisible(hasText);
        adjustSize();
    }
}
void RegisterWindow::onCreateAccount() {
    QString username = usernameEdit->text().trimmed();
    if (username.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username is required.");
        return;
    }
    QString password = passwordEdit->text();
    if (confirmVisible && password != confirmEdit->text()) {
        QMessageBox::warning(this, "Error", "Passwords do not match.");
        return;
    }
    if (AccountManager::createAccount(username, password, AccountManager::avatarPath())) {
        CongratsWindow *congrats = new CongratsWindow(username, this);
        congrats->show();
        this->hide();
    } else {
        QMessageBox::critical(this, "Error", "Could not create account.");
    }
}
void RegisterWindow::onPhantomMode() {
    WarningWindow *warn = new WarningWindow(this);
    warn->show();
    this->hide();
}
