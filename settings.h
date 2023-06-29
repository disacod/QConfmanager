#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QWidget>
#include <QSettings>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>

#define SETTINGS QSettings settings("AsmCoder","ConfMon");

#define SETTINGS_NEW_ROOM "notifications/newRoom"
#define SETTINGS_JOIN_SUBSCRIBER "notifications/newSubscriber"
#define SETTINGS_EXIT_SUBSCRIBER "notifications/exitSubscriber"

#define SETTINGS_SERT "sert/main"

#define SETTINGS_ASTERISK_NAME "asterisk/name"
#define SETTINGS_ASTERISK_IP   "asterisk/ip"
#define SETTINGS_ASTERISK_PORT  "asterisk/port"
#define SETTINGS_ASTERISK_LOGIN "asterisk/login"
#define SETTINGS_ASTERISK_PASSWORD "asterisk/password"
#define SETTINGS_ASTERISK_PROXY "asterisk/proxy"
#define SETTINGS_SYSTEM_NOTIFY "asterisk/system_notify"


#define SETTINGS_ASTERISK_SERVERS "config/servers"
#define SETTINGS_SERVER ""


struct Server {
    QString serverName;
    QString serverIp;
    QString serverPort;
    QString serverLogin;
    QString serverPassword;
    bool    serverProxy;
};

class Settings : public QObject
{
public:
    Settings();
    ~Settings();
    static void getServers(QList<Server>*);
//    static void showWindow();


private:


};

class SettingsServer : public QObject{
    Q_OBJECT
public:
    SettingsServer ();
    bool accept();
    QGroupBox *getGroupBox();
    bool checkInputs();

private:
    int index;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit_ip;
    QLineEdit *lineEdit_port;
    QLineEdit *lineEdit_login;
    QLineEdit *lineEdit_password;
    QCheckBox *checkBox_proxy;
    QComboBox *comboBox;
    void updateLines();
    void updateServers();
    void addServer();
    void writeServers();
    void removeServer(int);
    bool applyChanges(int);

private slots:
     void doComboBoxActivated(int);
     void doPlusButton();
     void doMinusButton();
     void doComboBoxText(QString);

};



class SettingsDialog :public QWidget{
    Q_OBJECT
public:
     SettingsDialog (QWidget *parent);



public slots:
     void accept();
     void reject();

signals:
    void onChange();

private:
     QGroupBox *miscSettingsGrpup();
     QGroupBox *serverSettingsGroup();

    SettingsServer * settingsServer;
     QCheckBox *checkBox_system_notify;
     QCheckBox *checkBox;
     QCheckBox *checkBox_2;
     QCheckBox *checkBox_3;



     void writeServers();


protected:

};

#endif // SETTINGS_H
