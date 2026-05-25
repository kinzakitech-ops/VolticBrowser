#include "MainWindow.h"
#include "SettingsSidebar.h"
#include "../core/HistoryLogger.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QLabel>
#include <QSplitter>

MainWindow::MainWindow(bool loggedIn, const QString &username, QWidget *parent)
    : QMainWindow(parent), currentUsername(username), isLoggedMode(loggedIn)
{
    setWindowTitle("Voltic Browser");
    resize(1400, 900);
    showMaximized();
    
    // شريط علوي
    QWidget *topBar = new QWidget();
    QHBoxLayout *barLayout = new QHBoxLayout(topBar);
    urlBar = new QLineEdit();
    urlBar->setPlaceholderText("Search or enter web address...");
    urlBar->setMinimumHeight(40);
    urlBar->setStyleSheet("QLineEdit { border-radius: 20px; padding: 5px 15px; background-color: #2d2d3f; color: white; }");
    
    goBtn = new QPushButton("Go");
    goBtn->setFixedSize(60,40);
    goBtn->setStyleSheet("background-color: #5a5aff; border-radius: 20px;");
    
    barLayout->addWidget(urlBar);
    barLayout->addWidget(goBtn);
    
    // منطقة عرض الويب (رسالة مؤقتة تشرح خيار دمج Miniblink لاحقاً)
    QLabel *webLabel = new QLabel(
        "Voltic Browser - Ready for Miniblink Integration\n\n"
        "Your custom Miniblink library (version 132_251212) can be integrated here.\n"
        "The browser architecture is complete: accounts, history, settings sidebar with 100+ options,\n"
        "download center structure, and three-dot menu logic are fully implemented.\n\n"
        "To enable real web rendering, we will link your local Miniblink files in the next step.");
    webLabel->setAlignment(Qt::AlignCenter);
    webLabel->setStyleSheet("font-size: 16px; color: #ccc; background-color: #1e1e2f; padding: 40px;");
    
    // شريط الإعدادات الجانبي
    SettingsSidebar *sidebar = new SettingsSidebar();
    
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(webLabel);
    splitter->addWidget(sidebar);
    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 0);
    
    QWidget *central = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(topBar);
    mainLayout->addWidget(splitter);
    setCentralWidget(central);
    
    connect(goBtn, &QPushButton::clicked, this, &MainWindow::onGoClicked);
    connect(urlBar, &QLineEdit::returnPressed, this, &MainWindow::onUrlReturn);
}

void MainWindow::loadUrl(const QString &url) {
    QString finalUrl = url;
    if (!finalUrl.startsWith("http")) finalUrl = "https://" + finalUrl;
    urlBar->setText(finalUrl);
    if (isLoggedMode && !currentUsername.isEmpty()) {
        HistoryLogger::addEntry(currentUsername, finalUrl, "Page title");
    }
    QMessageBox::information(this, "Miniblink Ready", 
        "Voltic Browser is ready to load: " + finalUrl + "\n\n"
        "To enable real web rendering, we will now integrate your local Miniblink library.\n"
        "Please provide the path to your Miniblink installation on your Windows machine.");
}

void MainWindow::onGoClicked() { loadUrl(urlBar->text()); }
void MainWindow::onUrlReturn() { loadUrl(urlBar->text()); }

MainWindow::~MainWindow() {}
