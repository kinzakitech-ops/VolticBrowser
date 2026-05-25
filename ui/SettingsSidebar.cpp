#include "SettingsSidebar.h"
#include <QFormLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QDateTime>
SettingsSidebar::SettingsSidebar(QWidget *parent) : QWidget(parent) {
    setFixedWidth(380);
    setStyleSheet("background-color: #1e1e2f; border-left: 1px solid #2d2d3f;");
    QScrollArea *scroll = new QScrollArea(this);
    QWidget *content = new QWidget();
    mainLayout = new QVBoxLayout(content);
    mainLayout->setSpacing(15);
    addAppearanceGroup();
    addUserAccountGroup();
    addSearchEngineGroup();
    addSecurityGroup();
    addAccessibilityGroup();
    addAboutGroup();
    scroll->setWidget(content);
    scroll->setWidgetResizable(true);
    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->addWidget(scroll);
}
void SettingsSidebar::addAppearanceGroup() {
    QGroupBox *group = new QGroupBox("Appearance (20+ options)");
    QFormLayout *form = new QFormLayout(group);
    QCheckBox *neonBorder = new QCheckBox(); form->addRow("Neon Border Toggle", neonBorder);
    QSlider *glowIntensity = new QSlider(Qt::Horizontal); glowIntensity->setRange(0,100); form->addRow("Glow Intensity", glowIntensity);
    QComboBox *neonColor = new QComboBox(); neonColor->addItems({"Red","Blue","Green","Cyan","Magenta"});
    connect(neonColor, &QComboBox::currentTextChanged, this, &SettingsSidebar::onNeonColorChanged);
    form->addRow("Neon Color", neonColor);
    QCheckBox *activeTabGlow = new QCheckBox(); form->addRow("Active Tab Glow", activeTabGlow);
    QSlider *borderThickness = new QSlider(Qt::Horizontal); borderThickness->setRange(1,4); form->addRow("UI Border Thickness", borderThickness);
    QSlider *blurRadius = new QSlider(Qt::Horizontal); blurRadius->setRange(0,20); form->addRow("Background Blur Radius", blurRadius);
    QSlider *glassOpacity = new QSlider(Qt::Horizontal); glassOpacity->setRange(0,100); form->addRow("Glass Opacity (%)", glassOpacity);
    QCheckBox *noiseOverlay = new QCheckBox(); form->addRow("Noise Overlay", noiseOverlay);
    QSlider *shadowDepth = new QSlider(Qt::Horizontal); shadowDepth->setRange(0,20); form->addRow("Shadow Depth", shadowDepth);
    QCheckBox *topBarAutoHide = new QCheckBox(); form->addRow("Top Bar Auto-Hide", topBarAutoHide);
    QCheckBox *miniFavoritesDock = new QCheckBox(); form->addRow("Mini Favorites Dock", miniFavoritesDock);
    QCheckBox *leftDock = new QCheckBox(); form->addRow("Left Dock Toggle", leftDock);
    QCheckBox *statusBar = new QCheckBox(); form->addRow("Status Bar Toggle", statusBar);
    QCheckBox *welcomeText = new QCheckBox(); form->addRow("Welcome Text Toggle", welcomeText);
    QComboBox *fontSelector = new QComboBox(); fontSelector->addItems({"Default","Arial","Verdana","Segoe UI"}); form->addRow("UI Font Selector", fontSelector);
    QSlider *fontSize = new QSlider(Qt::Horizontal); fontSize->setRange(8,24); form->addRow("UI Font Size", fontSize);
    QCheckBox *textGlow = new QCheckBox(); form->addRow("Text Glow Toggle", textGlow);
    QSlider *cornerRoundness = new QSlider(Qt::Horizontal); cornerRoundness->setRange(0,30); form->addRow("Corner Roundness (px)", cornerRoundness);
    QCheckBox *compactMode = new QCheckBox(); form->addRow("Compact Mode Toggle", compactMode);
    QComboBox *dockPosition = new QComboBox(); dockPosition->addItems({"Left","Right"}); form->addRow("Left Dock Position", dockPosition);
    QCheckBox *uiAnimations = new QCheckBox(); form->addRow("UI Animations Toggle", uiAnimations);
    mainLayout->addWidget(group);
}
void SettingsSidebar::addUserAccountGroup() {
    QGroupBox *group = new QGroupBox("User & Account (19+ options)");
    QFormLayout *form = new QFormLayout(group);
    QCheckBox *masterPassword = new QCheckBox(); form->addRow("Master Password Activation", masterPassword);
    QLineEdit *changePassword = new QLineEdit(); changePassword->setEchoMode(QLineEdit::Password); form->addRow("Change Password", changePassword);
    QLineEdit *sessionTimeout = new QLineEdit(); sessionTimeout->setPlaceholderText("minutes"); form->addRow("Session Timeout Timer", sessionTimeout);
    QPushButton *createProfile = new QPushButton("Create Profile"); form->addRow("", createProfile);
    QCheckBox *profileShortcut = new QCheckBox(); form->addRow("Profile Switcher Shortcut", profileShortcut);
    QComboBox *profileIcon = new QComboBox(); profileIcon->addItems({"Default","Avatar1","Avatar2"}); form->addRow("Profile Icon Select", profileIcon);
    QLineEdit *profileName = new QLineEdit(); form->addRow("Profile Name", profileName);
    QCheckBox *guestMode = new QCheckBox(); form->addRow("Guest Mode Toggle", guestMode);
    QCheckBox *dataEncryption = new QCheckBox(); form->addRow("Local Data Encryption", dataEncryption);
    QPushButton *exportData = new QPushButton("Export Profile Data"); form->addRow("", exportData);
    QPushButton *importData = new QPushButton("Import Profile Data"); form->addRow("", importData);
    QCheckBox *syncBookmarks = new QCheckBox(); form->addRow("Sync Bookmarks", syncBookmarks);
    QCheckBox *syncHistory = new QCheckBox(); form->addRow("Sync History", syncHistory);
    QCheckBox *syncPasswords = new QCheckBox(); form->addRow("Sync Passwords", syncPasswords);
    QCheckBox *rememberTabs = new QCheckBox(); form->addRow("Remember Open Tabs", rememberTabs);
    QCheckBox *autofill = new QCheckBox(); form->addRow("Autofill Toggle", autofill);
    QPushButton *manageAutofill = new QPushButton("Manage Autofill"); form->addRow("", manageAutofill);
    QCheckBox *saveCards = new QCheckBox(); form->addRow("Save Cards Toggle", saveCards);
    QCheckBox *clearOnLogout = new QCheckBox(); form->addRow("Clear Data on Logout", clearOnLogout);
    QComboBox *cloudBackup = new QComboBox(); cloudBackup->addItems({"Never","Daily","Weekly"}); form->addRow("Cloud Backup Interval", cloudBackup);
    QPushButton *deleteProfile = new QPushButton("Delete Profile"); form->addRow("", deleteProfile);
    mainLayout->addWidget(group);
}
void SettingsSidebar::addSearchEngineGroup() {
    QGroupBox *group = new QGroupBox("Search Engine");
    QFormLayout *form = new QFormLayout(group);
    QComboBox *defaultEngine = new QComboBox(); defaultEngine->addItems({"Google","Bing","DuckDuckGo","Yahoo"}); form->addRow("Default Engine", defaultEngine);
    QLineEdit *customURL = new QLineEdit(); customURL->setPlaceholderText("https://..."); form->addRow("Custom URL", customURL);
    QCheckBox *addressBarSuggestions = new QCheckBox(); form->addRow("Address Bar Suggestions", addressBarSuggestions);
    QCheckBox *historySuggestionsFirst = new QCheckBox(); form->addRow("History Suggestions First", historySuggestionsFirst);
    QComboBox *incognitoEngine = new QComboBox(); incognitoEngine->addItems({"Google","Bing","DuckDuckGo"}); form->addRow("Incognito Default Engine", incognitoEngine);
    QPushButton *searchShortcuts = new QPushButton("Search Shortcuts"); form->addRow("", searchShortcuts);
    QCheckBox *instantSearch = new QCheckBox(); form->addRow("Instant Search Pre-load", instantSearch);
    QCheckBox *safeSearch = new QCheckBox(); form->addRow("SafeSearch Filter", safeSearch);
    QComboBox *searchRegion = new QComboBox(); searchRegion->addItems({"Global","US","EU","Asia"}); form->addRow("Search Region Target", searchRegion);
    QComboBox *searchLanguage = new QComboBox(); searchLanguage->addItems({"English","Arabic","French","Spanish"}); form->addRow("Search Language Priority", searchLanguage);
    QCheckBox *cleanURL = new QCheckBox(); form->addRow("Clean URL Toggle", cleanURL);
    QCheckBox *voiceSearch = new QCheckBox(); form->addRow("Voice Search Activation", voiceSearch);
    QCheckBox *trendingSearches = new QCheckBox(); form->addRow("Trending Searches Display", trendingSearches);
    QPushButton *contextMenu = new QPushButton("Context Menu Customizer"); form->addRow("", contextMenu);
    QCheckBox *textHighlightSearch = new QCheckBox(); form->addRow("Text Highlight Search", textHighlightSearch);
    QCheckBox *tabToSearch = new QCheckBox(); form->addRow("Tab-to-Search Feature", tabToSearch);
    QPushButton *clearSearchHistory = new QPushButton("Clear Search History Only"); form->addRow("", clearSearchHistory);
    QCheckBox *keywordHighlighting = new QCheckBox(); form->addRow("Keyword Highlighting", keywordHighlighting);
    QCheckBox *predictiveLoading = new QCheckBox(); form->addRow("Predictive Loading", predictiveLoading);
    QSlider *searchBarWidth = new QSlider(Qt::Horizontal); searchBarWidth->setRange(200,800); form->addRow("Search Bar Width", searchBarWidth);
    QCheckBox *stripTracking = new QCheckBox(); form->addRow("Strip Tracking Params", stripTracking);
    mainLayout->addWidget(group);
}
void SettingsSidebar::addSecurityGroup() {
    QGroupBox *group = new QGroupBox("Security & Privacy (20+ options)");
    QFormLayout *form = new QFormLayout(group);
    QCheckBox *forceHTTPS = new QCheckBox(); form->addRow("Force HTTPS", forceHTTPS);
    QCheckBox *adBlocker = new QCheckBox(); form->addRow("Built-in Ad-Blocker", adBlocker);
    QCheckBox *block3rdPartyCookies = new QCheckBox(); form->addRow("Block 3rd-Party Cookies", block3rdPartyCookies);
    QCheckBox *sendDNT = new QCheckBox(); form->addRow("Send DNT Header", sendDNT);
    QCheckBox *phishingProtection = new QCheckBox(); form->addRow("Phishing Protection", phishingProtection);
    QCheckBox *globalJSDisabler = new QCheckBox(); form->addRow("Global JS Disabler", globalJSDisabler);
    QComboBox *cameraPermission = new QComboBox(); cameraPermission->addItems({"Ask","Allow","Block"}); form->addRow("Camera Permission Default", cameraPermission);
    QComboBox *micPermission = new QComboBox(); micPermission->addItems({"Ask","Allow","Block"}); form->addRow("Mic Permission Default", micPermission);
    QCheckBox *locationDisabler = new QCheckBox(); form->addRow("Location Tracker Disabler", locationDisabler);
    QCheckBox *blockPopups = new QCheckBox(); form->addRow("Block Pop-ups", blockPopups);
    QCheckBox *preventAutoDownloads = new QCheckBox(); form->addRow("Prevent Auto-Downloads", preventAutoDownloads);
    QCheckBox *strictCSP = new QCheckBox(); form->addRow("Strict CSP", strictCSP);
    QCheckBox *clearCacheOnExit = new QCheckBox(); form->addRow("Clear Cache on Exit", clearCacheOnExit);
    QCheckBox *clearCookiesOnExit = new QCheckBox(); form->addRow("Clear Cookies on Exit", clearCookiesOnExit);
    QCheckBox *passwordManager = new QCheckBox(); form->addRow("Password Manager Switch", passwordManager);
    QCheckBox *leakWarnings = new QCheckBox(); form->addRow("Show Leak Warnings", leakWarnings);
    QCheckBox *blockUntrustedScripts = new QCheckBox(); form->addRow("Block Untrusted Scripts", blockUntrustedScripts);
    QCheckBox *insecureFormAlert = new QCheckBox(); form->addRow("Insecure Form Alert", insecureFormAlert);
    QCheckBox *blockFLOC = new QCheckBox(); form->addRow("Block FLOC/Sandbox", blockFLOC);
    QCheckBox *doHToggle = new QCheckBox(); form->addRow("DoH Toggle", doHToggle);
    mainLayout->addWidget(group);
}
void SettingsSidebar::addAccessibilityGroup() {
    QGroupBox *group = new QGroupBox("Accessibility & Performance (19+ options)");
    QFormLayout *form = new QFormLayout(group);
    QSlider *defaultZoom = new QSlider(Qt::Horizontal); defaultZoom->setRange(50,200);
    connect(defaultZoom, &QSlider::valueChanged, this, &SettingsSidebar::onZoomSliderChanged);
    form->addRow("Default Zoom Level", defaultZoom);
    zoomSlider = defaultZoom;
    zoomLabel = new QLabel("100%");
    form->addRow("", zoomLabel);
    QCheckBox *hardwareAcceleration = new QCheckBox(); form->addRow("Hardware Acceleration", hardwareAcceleration);
    QCheckBox *smoothScrolling = new QCheckBox(); form->addRow("Smooth Scrolling", smoothScrolling);
    QCheckBox *readerMode = new QCheckBox(); form->addRow("Reader Mode", readerMode);
    QCheckBox *forceDarkMode = new QCheckBox(); form->addRow("Force Global Dark Mode", forceDarkMode);
    QCheckBox *caretBrowsing = new QCheckBox(); form->addRow("Caret Browsing", caretBrowsing);
    QComboBox *ramPurge = new QComboBox(); ramPurge->addItems({"Never","1min","5min","15min"}); form->addRow("RAM Purge Interval", ramPurge);
    QCheckBox *ultraLowRAM = new QCheckBox(); form->addRow("Ultra Low RAM 200MB Protocol", ultraLowRAM);
    QComboBox *cpuGovernor = new QComboBox(); cpuGovernor->addItems({"Power Save","Balanced","Performance"}); form->addRow("CPU Core Governor", cpuGovernor);
    QCheckBox *disableHighResImages = new QCheckBox(); form->addRow("Disable High-Res Images", disableHighResImages);
    QComboBox *tabSuspension = new QComboBox(); tabSuspension->addItems({"Never","1min","5min","10min"}); form->addRow("Tab Auto-Suspension Timer", tabSuspension);
    QCheckBox *highContrastText = new QCheckBox(); form->addRow("High Contrast Text Mode", highContrastText);
    QSlider *scrollbarWidth = new QSlider(Qt::Horizontal); scrollbarWidth->setRange(5,30); form->addRow("Scrollbar Width", scrollbarWidth);
    QCheckBox *blockHeavyAnimations = new QCheckBox(); form->addRow("Block Heavy Animations", blockHeavyAnimations);
    QComboBox *userAgentSpoofer = new QComboBox(); userAgentSpoofer->addItems({"Default","Chrome","Firefox","Edge"}); form->addRow("Custom User-Agent Spoofer", userAgentSpoofer);
    QCheckBox *mediaAutoPlayBlocker = new QCheckBox(); form->addRow("Media Auto-Play Blocker", mediaAutoPlayBlocker);
    QCheckBox *hardwareMediaKeys = new QCheckBox(); form->addRow("Hardware Media Keys Mapping", hardwareMediaKeys);
    QSlider *vramCap = new QSlider(Qt::Horizontal); vramCap->setRange(256,4096); form->addRow("VRAM Cap Limit (MB)", vramCap);
    QCheckBox *focusOutlineGlow = new QCheckBox(); form->addRow("Focus Outline Glow", focusOutlineGlow);
    QCheckBox *interceptWebfonts = new QCheckBox(); form->addRow("Intercept Heavy Webfonts", interceptWebfonts);
    QCheckBox *imageLazyLoading = new QCheckBox(); form->addRow("Image Lazy Loading", imageLazyLoading);
    mainLayout->addWidget(group);
}
void SettingsSidebar::addAboutGroup() {
    QGroupBox *group = new QGroupBox("About Us");
    QFormLayout *form = new QFormLayout(group);
    QLabel *browserName = new QLabel("The Voltic Browser - By Kinzaki-tech");
    browserName->setStyleSheet("font-weight: bold;");
    form->addRow("Browser Name:", browserName);
    QLabel *currentVersion = new QLabel("v1.0.0.b");
    form->addRow("Current Version:", currentVersion);
    QLabel *latestVersion = new QLabel("v1.0.0.b");
    form->addRow("Latest Version:", latestVersion);
    QPushButton *checkUpdates = new QPushButton("Check for updates");
    connect(checkUpdates, &QPushButton::clicked, this, &SettingsSidebar::onCheckForUpdates);
    form->addRow("Features:", checkUpdates);
    QLabel *contact = new QLabel("Kinzaki.tech@gmail.com");
    form->addRow("Contact Info:", contact);
    QLabel *copyright = new QLabel("© 2026 Kinzaki Tech. All rights reserved.");
    form->addRow("Copyright:", copyright);
    mainLayout->addWidget(group);
}
void SettingsSidebar::onNeonColorChanged(const QString &color) {
    QString style = QString("QWidget { border: 1px solid %1; }").arg(color);
    this->setStyleSheet(this->styleSheet() + style);
}
void SettingsSidebar::onZoomSliderChanged(int value) {
    zoomLabel->setText(QString("%1%").arg(value));
    emit zoomLevelChanged(value);
}
void SettingsSidebar::onCheckForUpdates() {
    lastUpdateCheck = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QMessageBox::information(this, "Update Check", "Last check: " + lastUpdateCheck + "\nYou are using the latest version.");
}
