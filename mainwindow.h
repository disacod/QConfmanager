#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "settings.h"
#include <QMainWindow>
#include <QSystemTrayIcon>
#include "notification.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void     showMessage(QString string);
    void showNotification(QString string);
    void setSettings (SettingsDialog *);

    ~MainWindow();

public slots:
       void exit();
       void tray();
       void settings();
//       void moveFromTrayIcon();
//       void moveToTrayIcon();

private slots:
       void trayActivation(QSystemTrayIcon::ActivationReason r);
protected:
       void closeEvent(QCloseEvent *event);
private:
       SettingsDialog  *mySettings;
       Notification    *notification;
//    Settings *settingsWindow;
    QSystemTrayIcon *systemTray;
       Ui::MainWindow *ui;
       QIcon    *icon;


};

#endif // MAINWINDOW_H
