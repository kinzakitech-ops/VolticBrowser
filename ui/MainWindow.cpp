#include "MainWindow.h"
#include "SettingsSidebar.h"
#include "DownloadCenter.h"
#include "../core/HistoryLogger.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTabWidget>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QMenu>
#include <QAction>
#include <QClipboard>
#include <QScreen>
#include <QPixmap>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QTimer>
#include <QTabBar>
#include <QSplitter>
MainWindow::MainWindow(bool loggedIn, const QString &username, QWidget *parent)
    : QMainWindow(parent), currentUsername(username), isLoggedMode(loggedIn), currentZoomLevel(100)
{
    setWindowTitle("Voltic Browser");
    resize(1400, 900);
    showMaximized();
    QWidget *topBar = new QWidget();
    QHBoxLayout *barLayout = new QHBoxLayout(topBar);
    barLayout->setContentsMargins(10,5,10,5);
    backBtn = new QPushButton("←");
    forwardBtn = new QPushButton("→");
    refreshBtn = new QPushButton("↻");
    backBtn->setFixedSize(40,36);
    forwardBtn->setFixedSize(40,36);
    refreshBtn->setFixedSize(40,36);
    urlBar = new QLineEdit();
    urlBar->setPlaceholderText("Search or enter web address...");
    urlBar->setMinimumHeight(36);
    urlBar->setStyleSheet("QLineEdit { border-radius: 18px; padding: 5px 15px; background-color: #2d2d3f; color: white; }");
    goBtn = new QPushButton("Go");
    goBtn->setFixedSize(60,36);
    goBtn->setStyleSheet("background-color: #5a5aff; border-radius: 18px;");
    menuBtn = new QPushButton("⋮");
    menuBtn->setFixedSize(40,36);
    menuBtn->setStyleSheet("font-size: 20px;");
    barLayout->addWidget(backBtn);
    barLayout->addWidget(forwardBtn);
    barLayout->addWidget(refreshBtn);
    barLayout->addWidget(urlBar, 1);
    barLayout->addWidget(goBtn);
    barLayout->addWidget(menuBtn);
    tabWidget = new QTabWidget();
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    connect(tabWidget, &QTabWidget::tabCloseRequested, [this](int index) {
        if (tabWidget->count() > 1) tabWidget->removeTab(index);
    });
    connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
    SettingsSidebar *sidebar = new SettingsSidebar();
    connect(sidebar, &SettingsSidebar::zoomLevelChanged, [this](int zoom) {
        currentZoomLevel = zoom;
        QWebEngineView *view = qobject_cast<QWebEngineView*>(tabWidget->currentWidget());
        if (view) view->setZoomFactor(zoom / 100.0);
    });
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(tabWidget);
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
    connect(backBtn, &QPushButton::clicked, this, &MainWindow::onBack);
    connect(forwardBtn, &QPushButton::clicked, this, &MainWindow::onForward);
    connect(refreshBtn, &QPushButton::clicked, this, &MainWindow::onRefresh);
    setupMenu();
    createTab("https://www.google.com");
}
void MainWindow::setupMenu() {
    QMenu *menu = new QMenu(this);
    QAction *newTabAct = new QAction("Open new tab", this);
    QAction *closeTabAct = new QAction("Close the current tab", this);
    QAction *closeAllAct = new QAction("Close all opened tabs", this);
    QAction *screenshotAct = new QAction("Do Screenshot", this);
    QAction *savePDFAct = new QAction("Save as PDF", this);
    QAction *saveHTMLAct = new QAction("Save as HTML", this);
    QAction *shareAct = new QAction("Share (Copy URL)", this);
    QAction *downloadsAct = new QAction("Download Center", this);
    QAction *settingsAct = new QAction("Settings", this);
    QAction *aboutAct = new QAction("About us", this);
    menu->addAction(newTabAct);
    menu->addAction(closeTabAct);
    menu->addAction(closeAllAct);
    menu->addSeparator();
    QWidget *zoomWidget = new QWidget();
    QHBoxLayout *zoomLayout = new QHBoxLayout(zoomWidget);
    QPushButton *zoomOut = new QPushButton("—");
    QPushButton *zoomIn = new QPushButton("+");
    QLabel *zoomLabel = new QLabel("100%");
    zoomLabel->setFixedWidth(50);
    zoomOut->setFixedSize(30,30);
    zoomIn->setFixedSize(30,30);
    zoomLayout->addWidget(zoomOut);
    zoomLayout->addWidget(zoomLabel);
    zoomLayout->addWidget(zoomIn);
    QAction *zoomAct = new QAction();
    zoomAct->setDefaultWidget(zoomWidget);
    menu->addAction(zoomAct);
    menu->addSeparator();
    menu->addAction(screenshotAct);
    QMenu *saveSubMenu = new QMenu("Save this tab as...", this);
    saveSubMenu->addAction(savePDFAct);
    saveSubMenu->addAction(saveHTMLAct);
    menu->addMenu(saveSubMenu);
    menu->addAction(shareAct);
    menu->addAction(downloadsAct);
    menu->addAction(settingsAct);
    menu->addAction(aboutAct);
    connect(newTabAct, &QAction::triggered, this, &MainWindow::onNewTab);
    connect(closeTabAct, &QAction::triggered, this, &MainWindow::onCloseTab);
    connect(closeAllAct, &QAction::triggered, this, &MainWindow::onCloseAllTabs);
    connect(zoomOut, &QPushButton::clicked, this, &MainWindow::onZoomOut);
    connect(zoomIn, &QPushButton::clicked, this, &MainWindow::onZoomIn);
    connect(screenshotAct, &QAction::triggered, this, &MainWindow::onScreenshot);
    connect(savePDFAct, &QAction::triggered, this, &MainWindow::onSaveAsPDF);
    connect(saveHTMLAct, &QAction::triggered, this, &MainWindow::onSaveAsHTML);
    connect(shareAct, &QAction::triggered, this, &MainWindow::onShareCopy);
    connect(downloadsAct, &QAction::triggered, this, &MainWindow::onOpenDownloadCenter);
    connect(settingsAct, &QAction::triggered, this, &MainWindow::onOpenSettings);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::onOpenAbout);
    menuBtn->setMenu(menu);
}
void MainWindow::createTab(const QString &url) {
    QWebEngineView *webView = new QWebEngineView();
    webView->setZoomFactor(currentZoomLevel / 100.0);
    connect(webView, &QWebEngineView::urlChanged, [this, webView](const QUrl &url) {
        if (tabWidget->currentWidget() == webView) urlBar->setText(url.toString());
        if (isLoggedMode && !currentUsername.isEmpty())
            HistoryLogger::addEntry(currentUsername, url.toString(), "Page");
    });
    connect(webView, &QWebEngineView::titleChanged, [this, webView](const QString &title) {
        int index = tabWidget->indexOf(webView);
        if (index != -1) tabWidget->setTabText(index, title.left(20));
    });
    int index = tabWidget->addTab(webView, "New Tab");
    tabWidget->setCurrentIndex(index);
    webView->load(QUrl(url));
}
void MainWindow::loadUrlInCurrentTab(const QString &url) {
    QWebEngineView *view = qobject_cast<QWebEngineView*>(tabWidget->currentWidget());
    if (view) {
        QString finalUrl = url;
        if (!finalUrl.startsWith("http") && !finalUrl.contains(".")) {
            finalUrl = "https://www.google.com/search?q=" + QUrl::toPercentEncoding(finalUrl);
        } else if (!finalUrl.startsWith("http")) {
            finalUrl = "https://" + finalUrl;
        }
        view->load(QUrl(finalUrl));
        urlBar->setText(finalUrl);
    }
}
void MainWindow::onGoClicked() { loadUrlInCurrentTab(urlBar->text()); }
void MainWindow::onUrlReturn() { loadUrlInCurrentTab(urlBar->text()); }
void MainWindow::onBack() { QWebEngineView *view = qobject_cast<QWebEngineView*>(tabWidget->currentWidget()); if (view) view->back(); }
void MainWindow::onForward() { QWebEngineView *view = qobject_cast<QWebEngineView*>(tabWidget->currentWidget()); if (view) view->forward(); }
void MainWindow::onRefresh() { QWebEngineView *view = qobject_cast<QWebEngineView*>(tabWidget->currentWidget()); if (view) view->reload(); }
void MainWindow::onNewTab() { createTab("https://www.google.com"); }
void MainWindow::onCloseTab() { int idx = tabWidget->currentIndex(); if (idx != -1 && tabWidget->count() > 1) tabWidget->removeTab(idx); }
void MainWindow::onCloseAllTabs() { while (tabWidget->count() > 1) tabWidget->removeTab(1); }
void MainWindow::onZoomIn() { currentZoomLevel += 10; if (currentZoomLevel > 200) currentZoomLevel = 200; updateZoom(0); }
void MainWindow::onZoomOut() { currentZoomLevel -= 10; if (currentZoomLevel < 30) currentZoomLevel = 30; updateZoom(0); }
void MainWindow::onZoomReset() { currentZoomLevel = 100; updateZoom(0); }
void MainWindow::updateZoom(int) { QWebEngineView *view = qobject_cast<QWebEngineView*>(tabWidget->currentWidget()); if (view) view->setZoomFactor(currentZoomLevel / 100.0); }
void MainWindow::onScreenshot() {
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(0);
    QString fileName = QFileDialog::getSaveFileName(this, "Save Screenshot", "screenshot.png", "PNG (*.png)");
    if (!fileName.isEmpty()) pixmap.save(fileName);
}
void MainWindow::onSaveAsPDF() {
    QWebEngineView *view = qobject_cast<QWebEngineView*>(tabWidget->currentWidget());
    if (view) {
        QString fileName = QFileDialog::getSaveFileName(this, "Save as PDF", "page.pdf", "PDF (*.pdf)");
        if (!fileName.isEmpty()) view->page()->printToPdf(fileName);
    }
}
void MainWindow::onSaveAsHTML() {
    QWebEngineView *view = qobject_cast<QWebEngineView*>(tabWidget->currentWidget());
    if (view) {
        QString fileName = QFileDialog::getSaveFileName(this, "Save HTML", "page.html", "HTML (*.html)");
        if (!fileName.isEmpty()) {
            view->page()->toHtml([fileName](const QString &html) {
                QFile file(fileName);
                if (file.open(QIODevice::WriteOnly)) file.write(html.toUtf8());
            });
        }
    }
}
void MainWindow::onShareCopy() {
    QWebEngineView *view = qobject_cast<QWebEngineView*>(tabWidget->currentWidget());
    if (view) {
        QString url = view->url().toString();
        QGuiApplication::clipboard()->setText(url);
        QMessageBox::information(this, "Copied", "URL copied to clipboard:\n" + url);
    }
}
void MainWindow::onOpenDownloadCenter() {
    DownloadCenter *center = new DownloadCenter(this);
    center->addDownload("https://example.com/file.zip", "example.zip");
    center->exec();
}
void MainWindow::onOpenSettings() {
    QMessageBox::information(this, "Settings", "Settings panel is already available on the right sidebar.");
}
void MainWindow::onOpenAbout() {
    QMessageBox::about(this, "About Voltic Browser",
        "<b>The Voltic Browser - By Kinzaki-tech</b><br>"
        "Version: v1.0.0.b<br>"
        "Latest: v1.0.0.b<br>"
        "Contact: Kinzaki.tech@gmail.com<br>"
        "© 2026 Kinzaki Tech. All rights reserved.");
}
void MainWindow::onTabChanged(int index) {
    if (index != -1) {
        QWebEngineView *view = qobject_cast<QWebEngineView*>(tabWidget->widget(index));
        if (view) urlBar->setText(view->url().toString());
    }
}
MainWindow::~MainWindow() {}
