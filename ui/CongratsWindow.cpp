#include "CongratsWindow.h"
#include "MainWindow.h"
#include <QLabel>
#include <QVBoxLayout>
CongratsWindow::CongratsWindow(const QString &username, QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Success");
    setFixedSize(550, 400);
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setAlignment(Qt::AlignCenter);
    QLabel *msg = new QLabel(QString(
        "congratulation!\n\n"
        "You have been successfully setting up your account - Mr. %1\n\n"
        "you can now enjoy the full browsing experience and try all the features without any problems.\n\n"
        "If you face any problems.. Please contact us at:\nkinzaki.tech@gmail.com"
    ).arg(username));
    msg->setAlignment(Qt::AlignCenter);
    msg->setWordWrap(true);
    msg->setStyleSheet("font-size: 14px;");
    layout->addWidget(msg);
    setCentralWidget(central);
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &CongratsWindow::onTimeout);
    timer->start(6000);
}
void CongratsWindow::onTimeout() {
    MainWindow *mainWin = new MainWindow(true);
    mainWin->show();
    this->close();
}
