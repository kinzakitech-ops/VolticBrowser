#include <QApplication>
#include <QDir>
#include "core/FileManager.h"
#include "core/AccountManager.h"
#include "ui/RegisterWindow.h"
#include "ui/LoginWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyle("Fusion");
    QString installPath = QCoreApplication::applicationDirPath();
    FileManager::initializeInstallPath(installPath);
    QList<QString> accounts = AccountManager::getAllUsernames();
    if (accounts.isEmpty()) {
        RegisterWindow reg;
        reg.show();
    } else {
        LoginWindow login;
        login.show();
    }
    return app.exec();
}
