#ifndef ASTERISK_H
#define ASTERISK_H

#include "room.h"
#include <string>
#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <QThread>
#include <QTcpSocket>
#include <QTimer>
#include "settings.h"

enum LoginState {LOGIN_UNSET,LOGIN_SUCCESSEFUL,LOGIN_FAIL};


class Asterisk : public QObject
{
    Q_OBJECT

public:

    explicit Asterisk(QObject *parent =nullptr);
    ~Asterisk();

    void setServer(Server server, int index);
    const QString getServerName();
    void    run();
    void    stop();
    bool confBridgeMute(sSubscriber *s);
    bool confBridgeUnMute(sSubscriber *s);
    bool confBridgeKick(sSubscriber *s);
    bool confBridgeSayMute(sSubscriber *s);
    bool confBridgeSayUnMute(sSubscriber *s);
private:
    int         myIndex;
    Server      server;
    QTcpSocket *socket;
//    QDataStream in;

    LoginState loginState;

    QTimer   *pingTimer;
    QTimer   *reconnectTimer;
    QTimer   *loginTimer;


    bool    login(const char * login, const char * passwd);
    bool    logoff();
    void    parse(const char *);
    sSubscriber extractSubscriber(std::string,bool);
    bool    confBridgeList(std::string room);
    bool    confBridgeListRooms();
    void    reConnect();
    void    extractRooms(std::string line, bool init);
    void    substr_test(std::string strin, const char * strtst);

signals:
    void    onNetworkFail();
    void    onLogin(bool);
    void    onSubscriber(REASON, sSubscriber);
//    void    onDoPing();
    void    onDoRun();
    void    onDoLogin();

private slots:


    bool    managerActionPing();
    bool    connectToHost();
//    bool    writeData(QByteArray data);
//    bool readData(QByteArray data, int size);
    void onStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();
    void    doRun();
    void    doLogin();
};

#endif // ASTERISK_H
