#ifndef SETTINGSSIDEBAR_H
#define SETTINGSSIDEBAR_H
#include <QWidget>
#include <QGroupBox>
#include <QCheckBox>
#include <QSlider>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
class SettingsSidebar : public QWidget {
    Q_OBJECT
public:
    explicit SettingsSidebar(QWidget *parent = nullptr);
signals:
    void appearanceChanged();
    void zoomLevelChanged(int zoom);
private slots:
    void onNeonColorChanged(const QString &color);
    void onZoomSliderChanged(int value);
    void onCheckForUpdates();
private:
    QVBoxLayout *mainLayout;
    QSlider *zoomSlider;
    QLabel *zoomLabel;
    QString lastUpdateCheck;
    void addAppearanceGroup();
    void addUserAccountGroup();
    void addSearchEngineGroup();
    void addSecurityGroup();
    void addAccessibilityGroup();
    void addAboutGroup();
};
#endif
