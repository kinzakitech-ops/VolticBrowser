#include "WarningWindow.h"
#include "MainWindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
WarningWindow::WarningWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Warning");
    setFixedSize(600, 300);
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    QLabel *warn = new QLabel(
        "Warning!!\n\n"
        "When you browse the net as a phantom with «Voltic_Browser» data like the browsing history, "
        "your accounts, passwords, cookies will be lost after you close the browser and nothing will be saved ..."
    );
    warn->setAlignment(Qt::AlignCenter);
    warn->setWordWrap(true);
    QPushButton *continueBtn = new QPushButton("Continue");
    connect(continueBtn, &QPushButton::clicked, this, &WarningWindow::onContinue);
    layout->addWidget(warn);
    layout->addWidget(continueBtn);
    setCentralWidget(central);
}
void WarningWindow::onContinue() {
    MainWindow *mainWin = new MainWindow(false);
    mainWin->show();
    this->close();
}
