#include "settings.h"

#include <QVBoxLayout>

#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QDebug>
#include <QList>





QList<Server> servers;

Settings::Settings()
{
    qDebug("Settings constructor");
}
/*
void    Settings::showWindow(){

    qDebug("Settigs window");
//    QWidget *mainWidget = new QWidget();
    new SettingsDialog(nullptr);
}

*/

void Settings::getServers(QList<Server>* s){
    SETTINGS
    s->clear();
    int size = settings.beginReadArray(SETTINGS_ASTERISK_SERVERS);
    for (int i = 0; i < size; i++) {
        settings.setArrayIndex(i);
        Server server;
        server.serverName = settings.value(SETTINGS_ASTERISK_NAME, QString::fromUtf8("Сервер № ").append(QString::number(i+1))).toString();
        server.serverIp = settings.value(SETTINGS_ASTERISK_IP,QString::fromUtf8("127.0.0.1")).toString();
        server.serverPort = settings.value(SETTINGS_ASTERISK_PORT,QString::fromUtf8("5038")).toString();
        server.serverLogin = settings.value(SETTINGS_ASTERISK_LOGIN,QString::fromUtf8("")).toString();
        server.serverPassword = settings.value(SETTINGS_ASTERISK_PASSWORD,QString::fromUtf8("")).toString();
        server.serverProxy = settings.value((SETTINGS_ASTERISK_PROXY),false).toBool();
        s->append(server);
    }

    settings.endArray();
}

Settings::~Settings()
{

}


SettingsServer::SettingsServer (){
    SETTINGS
    servers.clear();
    updateServers();
    index=0;
    groupBox_2 = new QGroupBox();

    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    groupBox_2->setTitle(QString::fromUtf8("Asterisk AMI"));
    QGridLayout *gridLayout = new QGridLayout(groupBox_2);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    comboBox = new QComboBox();
    comboBox->setObjectName(QString::fromUtf8("combo_1"));
    comboBox->setEditable(true);
    comboBox->setInsertPolicy(QComboBox::NoInsert);

    for (int i = 0; i < servers.size();++i) {
        comboBox->addItem(servers.at(i).serverName);
    }

    QObject::connect(comboBox,SIGNAL (activated(int)),this,SLOT (doComboBoxActivated(int)));
    QObject::connect(comboBox,SIGNAL (currentTextChanged(QString)),this,SLOT(doComboBoxText(QString)));

    gridLayout->addWidget(comboBox,0,1,1,1);


    QLabel *label_2 = new QLabel();
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setText(QString::fromUtf8("Login"));
    gridLayout->addWidget(label_2, 3, 0, 1, 1);

    QLabel *label_ip = new QLabel();
    label_ip->setObjectName(QString::fromUtf8("label"));
    label_ip->setText(QString::fromUtf8("IP"));
    gridLayout->addWidget(label_ip, 1, 0, 1, 1);
    lineEdit_ip = new QLineEdit();
    lineEdit_ip->setObjectName(QString::fromUtf8("lineEdit_ip"));
//    lineEdit_ip->setText(settings.value(SETTINGS_ASTERISK_IP,"10.88.210.25").toString());
    gridLayout->addWidget(lineEdit_ip, 1, 1, 1, 1);

    QLabel *label_port = new QLabel();
    label_port->setObjectName(QString::fromUtf8("label_port"));
    label_port->setText(QString::fromUtf8("Port"));
    gridLayout->addWidget(label_port, 2, 0, 1, 1);
    lineEdit_port = new QLineEdit();
    lineEdit_port->setObjectName(QString::fromUtf8("lineEdit_port"));
//    lineEdit_port->setText(settings.value(SETTINGS_ASTERISK_PORT,"5038").toString());
    gridLayout->addWidget(lineEdit_port, 2, 1, 1, 1);

    lineEdit_login = new QLineEdit();
    lineEdit_login->setObjectName(QString::fromUtf8("lineEdit_2"));
//    lineEdit_login->setText(settings.value(SETTINGS_ASTERISK_LOGIN,"admin").toString());

    gridLayout->addWidget(lineEdit_login, 3, 1, 1, 1);

    QLabel *label_3 = new QLabel();
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setText(QString::fromUtf8("Password"));

    gridLayout->addWidget(label_3, 4, 0, 1, 1);

    lineEdit_password = new QLineEdit();
    lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_3"));
    lineEdit_password->setEchoMode(QLineEdit::Password);
    gridLayout->addWidget(lineEdit_password, 4, 1, 1, 1);
//    lineEdit_password->setText(settings.value(SETTINGS_ASTERISK_PASSWORD,"admin").toString());

    checkBox_proxy = new QCheckBox();
    checkBox_proxy->setText(QString::fromUtf8("Использовасть системный прокси"));

    gridLayout->addWidget(checkBox_proxy,5,1,1,1);

    QGridLayout *buttonLayout = new QGridLayout();
    buttonLayout->setSpacing(1);
    buttonLayout->setContentsMargins(0,0,1,0);

    QPushButton *plusButton = new QPushButton("+");
    QPushButton *minusButton = new QPushButton("-");

    plusButton->setMaximumWidth(30);
    minusButton->setMaximumWidth(30);

    buttonLayout->addWidget(plusButton,0,0,1,1);
    buttonLayout->addWidget(minusButton,0,1,1,1);

    gridLayout->addLayout(buttonLayout,0,0,1,1);




    connect(plusButton,SIGNAL(clicked()),this,SLOT (doPlusButton()));
    connect(minusButton,SIGNAL(clicked()),this,SLOT (doMinusButton()));


    updateLines();


}

void SettingsServer::doComboBoxText(QString string){
    qDebug("Text changed");
    comboBox->setItemText(comboBox->currentIndex(),string);
}

void SettingsServer::doPlusButton(){
    addServer();
}
void SettingsServer::doMinusButton(){
    removeServer(0);
}

QGroupBox* SettingsServer::getGroupBox(){

    return groupBox_2;
}


void SettingsServer::addServer(){
    SETTINGS
    Server server;

    if (checkInputs()) return;

    int index=comboBox->currentIndex();
    applyChanges(index);



    server.serverName = QString::fromUtf8("Новый сервер ").append(QString::number(servers.size()));
    server.serverIp = "127.0.0.1";
    server.serverPort = "5038";
    server.serverLogin = "";
    server.serverPassword = "";
    servers.append(server);
    comboBox->addItem(server.serverName);
    comboBox->setCurrentIndex(comboBox->count()-1);

    updateLines();
}

void SettingsServer::removeServer(int index){
    index = comboBox->currentIndex();
    if (index==0) return;
    comboBox->removeItem(index);
    servers.removeAt(index);
    updateLines();

}

void SettingsServer::updateLines(){
    index=comboBox->currentIndex();
    if (index>=servers.size()) return;
    lineEdit_ip->setText(servers.at(index).serverIp);
    lineEdit_port->setText(servers.at(index).serverPort);
    lineEdit_login->setText(servers.at(index).serverLogin);
    lineEdit_password->setText(servers.at(index).serverPassword);
    checkBox_proxy->setChecked(servers.at(index).serverProxy);
}

void SettingsServer::doComboBoxActivated(int index) {

    static int previusIndex=0;
    if (checkInputs()){
        comboBox->setCurrentIndex(previusIndex);
        return;
    }
    applyChanges(previusIndex);
    previusIndex=index;
    updateLines();

}

bool SettingsServer::applyChanges(int index){
    Server server;
    if (checkInputs()) return true;
    server.serverName=comboBox->itemText(index);
    server.serverIp=lineEdit_ip->text();
    server.serverPort=lineEdit_port->text();
    server.serverLogin=lineEdit_login->text();
    server.serverPassword=lineEdit_password->text();
    server.serverProxy=checkBox_proxy->isChecked();

    servers.replace(index,server);
    return false;
}

bool SettingsServer::checkInputs(){
    bool error=false;
    QRegExp reg_ip("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)?$");
    QRegExp reg_port("^(([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5]))?$");

if (reg_ip.indexIn(lineEdit_ip->text())<0) {
 lineEdit_ip->setStyleSheet("QLineEdit { background: rgb(255, 0, 0); selection-background-color: rgb(233, 99, 0); }");
 error = true;
} else {
lineEdit_ip->setStyleSheet("");
}

if (reg_port.indexIn(lineEdit_port->text())<0) {
 lineEdit_port->setStyleSheet("QLineEdit { background: rgb(255, 0, 0); selection-background-color: rgb(233, 99, 0); }");
 error = true;
} else {
    lineEdit_port->setStyleSheet("");
}
return error;
}

bool SettingsServer::accept(){

    if (applyChanges(comboBox->currentIndex())) return true;

    SETTINGS
    settings.beginWriteArray(SETTINGS_ASTERISK_SERVERS);
    settings.clear();
    for (int i = 0; i < servers.size(); i++){
        settings.setArrayIndex(i);
        settings.setValue(SETTINGS_ASTERISK_NAME,servers.at(i).serverName);
        settings.setValue(SETTINGS_ASTERISK_IP,servers.at(i).serverIp);
        settings.setValue(SETTINGS_ASTERISK_PORT,servers.at(i).serverPort);
        settings.setValue(SETTINGS_ASTERISK_LOGIN,servers.at(i).serverLogin);
        settings.setValue(SETTINGS_ASTERISK_PASSWORD,servers.at(i).serverPassword);
        settings.setValue(SETTINGS_ASTERISK_PROXY,servers.at(i).serverProxy);
    }

    settings.endArray();
    return false;
}

    SettingsDialog::SettingsDialog (QWidget *parent) :QWidget (parent) {
        SETTINGS
        setObjectName(QString::fromUtf8("Settings"));

        QVBoxLayout *verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout_2"));

        verticalLayout->addWidget(miscSettingsGrpup());

        settingsServer = new SettingsServer();
        verticalLayout->addWidget(settingsServer->getGroupBox());
 //       verticalLayout_2->addWidget(groupBox_2);

        QDialogButtonBox *buttonBox = new QDialogButtonBox();
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);


        verticalLayout->addWidget(buttonBox);
        setLayout(verticalLayout);

        connect(buttonBox,SIGNAL(accepted()),this, SLOT(accept()));
        connect(buttonBox,SIGNAL(rejected()),this, SLOT(reject()));
        resize(513, 328);
        setWindowTitle(QString::fromUtf8("Настройки"));
//        show();
    }






    void SettingsDialog::accept(){
        qDebug("Accepted");
        SETTINGS
        if (settingsServer->accept()) return;

        settings.setValue (SETTINGS_SYSTEM_NOTIFY,checkBox_system_notify->isChecked());
        settings.setValue (SETTINGS_NEW_ROOM,checkBox->isChecked());
        settings.setValue (SETTINGS_JOIN_SUBSCRIBER,checkBox_2->isChecked());
        settings.setValue (SETTINGS_EXIT_SUBSCRIBER,checkBox_3->isChecked());

        emit onChange();

        close();
    }

    void SettingsDialog::reject(){
        close();
    }

    void SettingsServer::updateServers(){
        SETTINGS

        int size = settings.beginReadArray(SETTINGS_ASTERISK_SERVERS);
        if (size == 0) size = 1;

        for (int i = 0; i < size; i++) {
            settings.setArrayIndex(i);
            Server server;
            server.serverName = settings.value(SETTINGS_ASTERISK_NAME, QString::fromUtf8("Сервер № ").append(QString::number(i+1))).toString();
            server.serverIp = settings.value(SETTINGS_ASTERISK_IP,QString::fromUtf8("127.0.0.1")).toString();
            server.serverPort = settings.value(SETTINGS_ASTERISK_PORT,QString::fromUtf8("5038")).toString();
            server.serverLogin = settings.value(SETTINGS_ASTERISK_LOGIN,QString::fromUtf8("")).toString();
            server.serverPassword = settings.value(SETTINGS_ASTERISK_PASSWORD,QString::fromUtf8("")).toString();
            server.serverProxy = settings.value(SETTINGS_ASTERISK_PROXY,false).toBool();
            servers.append(server);
        }

        settings.endArray();
    }


    void SettingsServer::writeServers(){
        SETTINGS
        int size = servers.size();
        settings.beginReadArray(SETTINGS_ASTERISK_SERVERS);
        for (int i = 0; i < size; ++i){
            settings.setArrayIndex(i);
            settings.setValue(SETTINGS_ASTERISK_NAME, servers.at(i).serverName);
            settings.setValue(SETTINGS_ASTERISK_IP,servers.at(i).serverIp);
            settings.setValue(SETTINGS_ASTERISK_PORT,servers.at(i).serverPort);
            settings.setValue(SETTINGS_ASTERISK_LOGIN,servers.at(i).serverLogin);
            settings.setValue(SETTINGS_ASTERISK_PASSWORD,servers.at(i).serverPassword);
            settings.setValue(SETTINGS_ASTERISK_PROXY,servers.at(i).serverProxy);
        }

        settings.endArray();
    }


    QGroupBox *SettingsDialog::miscSettingsGrpup(){
        SETTINGS
        QGroupBox *groupBox = new QGroupBox();
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setTitle(QString::fromUtf8("Уведомления"));
        QVBoxLayout *verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        checkBox_system_notify = new QCheckBox(groupBox);
        checkBox_system_notify->setObjectName(QString::fromUtf8("checkBox"));
        checkBox_system_notify->setText(QString::fromUtf8("Системные уведомления"));
        checkBox_system_notify->setChecked(settings.value(SETTINGS_SYSTEM_NOTIFY,false).toBool());
        verticalLayout->addWidget(checkBox_system_notify);


        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setText(QString::fromUtf8("Создание новой комнаты"));
        checkBox->setChecked(settings.value(SETTINGS_NEW_ROOM,true).toBool());
        verticalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setText(QString::fromUtf8("Присоединение нового участника"));
        checkBox_2->setChecked(settings.value(SETTINGS_JOIN_SUBSCRIBER,true).toBool());
        verticalLayout->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(groupBox);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setText(QString::fromUtf8("Выход участника из комнаты"));
        checkBox_3->setChecked(settings.value(SETTINGS_EXIT_SUBSCRIBER,true).toBool());
        verticalLayout->addWidget(checkBox_3);

        return groupBox;

    }
