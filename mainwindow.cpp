//#include <QResource>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui.h"

#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    notification = new Notification(nullptr);
    Q_INIT_RESOURCE(icons);

    icon = new QIcon(":/icon/rc/icon.png");



    systemTray = new QSystemTrayIcon(this);
    systemTray->setIcon(*icon);


    QAction * menuExit = new QAction(QString::fromUtf8("Выход"),this);
    QAction * trayIcon = new QAction(QString::fromUtf8("Показать, скрыть"),this);
    QAction * settingsMenu = new QAction(QString::fromUtf8("Настройка"),this);
    ui->menuFile->addAction(trayIcon);
    ui->menuFile->addAction(settingsMenu);
    ui->menuFile->addSeparator();
    ui->menuFile->addAction(menuExit);

    systemTray->setContextMenu(ui->menuFile);


    connect(menuExit,SIGNAL(triggered()),this,SLOT(exit()));
    connect(trayIcon,SIGNAL(triggered()),this,SLOT(tray()));
    connect(settingsMenu,SIGNAL(triggered()),this,SLOT(settings()));

    connect(systemTray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(trayActivation(QSystemTrayIcon::ActivationReason)));



    if (!systemTray->isSystemTrayAvailable()) trayIcon->setDisabled(true);


    systemTray->show();

}

void    MainWindow::showMessage(QString string){

    ui->statusBar->showMessage(string);
}

void    MainWindow::showNotification(QString string){
            SETTINGS
            if (settings.value(SETTINGS_SYSTEM_NOTIFY).toBool()){
                QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
                systemTray->showMessage(QString::fromUtf8("Монитор конфиренций"), string,icon,4000);
                } else {

                    notification->setPopupText(string);
                    notification->show();
                }

}

void MainWindow::closeEvent(QCloseEvent *event){
    if (this->isVisible() ){
        event->ignore();
        MainWindow::tray();

    }
}
void MainWindow::setSettings(SettingsDialog *s){
    mySettings = s;
}
void MainWindow::settings(void){

    mySettings->show();
//        new SettingsDialog(nullptr);
//    Settings::showWindow();
}

void MainWindow::exit(void){
    QApplication::quit();

}

void MainWindow::tray()
{

    if(!this->isVisible()){
        this->show();
    } else {
        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

        systemTray->showMessage("ConfBridge Monitor",
                              "Приложение свернуто в трей. Для того чтобы, "
                                     "развернуть окно приложения, щелкните по иконке приложения в трее",
                              icon,
                              4000);
        this->hide();
    }

}


void    MainWindow::trayActivation(QSystemTrayIcon::ActivationReason r){

    switch (r) {
        case    QSystemTrayIcon::Trigger:

        if (this->isVisible())
            this->hide();
        else
            this->show();

        break;

    default:
        break;

    }
}

MainWindow::~MainWindow()
{

    delete ui;

}



