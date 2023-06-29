#include "asterisk.h"
#include "settings.h"
#include <QHostAddress>
#include <QNetworkProxy>
#include <iostream>

//#define TEST_MODE



Asterisk::Asterisk(QObject * parent) : QObject(parent)
{
    loginState=LOGIN_UNSET;
//    QObject::connect(this, SIGNAL (onDoPing()),this, SLOT (managerActionPing()));
    connect(this,SIGNAL(onDoRun()),this,SLOT(doRun()));
    connect(this,SIGNAL (onDoLogin()),this, SLOT(doLogin()));
    socket = new QTcpSocket(this);
    pingTimer = new QTimer(this);
    loginTimer = new QTimer(this);
    reconnectTimer = new QTimer(this);
    connect(loginTimer,SIGNAL (timeout()),this, SLOT (doLogin()));
    connect (reconnectTimer,SIGNAL (timeout()), this, SLOT (doRun()));
    connect (pingTimer, SIGNAL (timeout()), this, SLOT (managerActionPing()));

#ifndef TEST_MODE
    connect(socket, SIGNAL (readyRead()),this,SLOT (onReadyRead()));
    connect(socket, SIGNAL (stateChanged(QAbstractSocket::SocketState)),this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
#endif
}

const QString Asterisk::getServerName(){
    return server.serverName;
}

void    Asterisk::setServer (Server s, int i){
        server=s;
        myIndex=i;
}

bool    Asterisk::connectToHost(){
#ifndef TEST_MODE
        QString host_str = server.serverIp;
        QString host_port = server.serverPort;
//        QHostAddress *hostAddress = new QHostAddress(host_str);
        if (!server.serverProxy) socket->setProxy(QNetworkProxy::NoProxy);
        socket->connectToHost(QHostAddress(host_str) ,host_port.toInt());
        return socket->waitForConnected();
#else
    return false;


#endif
}

void Asterisk::onStateChanged(QAbstractSocket::SocketState socketState){
#ifndef TEST_MODE
    switch (socketState) {
    case QAbstractSocket::UnconnectedState:
        qDebug("Socket state change to unconnected state");
        pingTimer->stop();
        loginTimer->stop();
        socket->abort();
        if (loginState!=LOGIN_FAIL)
            emit onNetworkFail();
        else
            emit onLogin(false);
        reConnect();
        break;
    case QAbstractSocket::ConnectedState:
        qDebug("Socket state change to connected state");
        reconnectTimer->stop();
        pingTimer->stop();
        loginTimer->setInterval(3000);
        loginTimer->start();

        break;
    default:
        break;

    }
#endif
}
/*
bool    Asterisk::writeData (QByteArray data){
#ifndef TEST_MODE
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        socket->write(data, data.size()); //write the data itself
        return socket->waitForBytesWritten();
    }
    else
#endif
        return false;
}
*/
void Asterisk::onReadyRead(){
    int size=socket->bytesAvailable();
    if (size<=0) return;
//    std::cout << "DATA AWAILABLE!!!!! " << size << "\r\n";

    while (!socket->atEnd()) {
        Asterisk::parse(socket->read(1));
    }

}

void Asterisk::reConnect(){

    reconnectTimer->setInterval(3000);
    reconnectTimer->start();

}

void Asterisk::doRun(){

    run();
}

void    Asterisk::doLogin(){
    Asterisk::login(server.serverLogin.toStdString().data(),server.serverPassword.toStdString().data());
}

void Asterisk::run(){
#ifndef TEST_MODE
    socket->abort();
     if (Asterisk::connectToHost()){
          qDebug("Connected to Asterisk");
//          Asterisk::doLogin();
     } else {

     }
#else

    for (int i=0; i<7; i++)
    {
        sSubscriber *subscriber = new sSubscriber;
        subscriber->conf = "1234";
        subscriber->name = "Name";
        subscriber->number = std::to_string(i);
        subscriber->serverName = server.serverName.toStdString();
        subscriber->serverNum = myIndex;
        subscriber->channel = "Local "+std::to_string(i);
        Room::pushSubscriber(Room::JOIN,*subscriber);
        emit onSubscriber(Room::JOIN);
    }

#endif
}

void    Asterisk::stop(){
    reconnectTimer->stop();
    loginTimer->stop();
    pingTimer->stop();
    disconnect(this,SIGNAL(onDoRun()),this,SLOT(doRun()));
    disconnect(this,SIGNAL (onDoLogin()),this, SLOT(doLogin()));
    disconnect(loginTimer,SIGNAL (timeout()),this, SLOT (doLogin()));
    disconnect (reconnectTimer,SIGNAL (timeout()), this, SLOT (doRun()));
    disconnect (pingTimer, SIGNAL (timeout()), this, SLOT (managerActionPing()));
    disconnect(socket, SIGNAL (readyRead()),this,SLOT (onReadyRead()));
    disconnect(socket, SIGNAL (stateChanged(QAbstractSocket::SocketState)),this, SLOT(onStateChanged(QAbstractSocket::SocketState)));


    socket->abort();
}

bool    Asterisk::login(const char * login, const char * passwd){
    bool result=false;
    std::string str;
    str.append("Action: Login\r\nUsername: ").append(login).append("\r\nSecret: ").append(passwd).append("\r\n\r\n");

    socket->write(str.data(),str.length());
    return result;
    }

bool    Asterisk::logoff(){
    std::string str;
    str.append("Action: Logoff\r\nParameters: None\r\n\r\n");
//    ::send(sd,str.data(),str.length(),0);
    socket->write(str.data(),str.length());
    return true;
}

bool    Asterisk::confBridgeListRooms(){
    std::string str;
    str.append("Action: ConfbridgeListRooms\r\n\r\n");
    socket->write(str.data(),str.length());
//    ::send(sd,str.data(),str.length(),0);
    return true;
}

bool Asterisk::managerActionPing()
{
//    qDebug("Check status...");
    static unsigned id=0;
    static std::string ids="";

    std::string str;
    str.append("Action: Ping\r\nActionID: ").append(ids).append("\r\n\r\n");
    socket->write(str.data(),str.length());
//    ::send(sd,str.data(),str.length(),0);
    id++;
    return true;
}

bool    Asterisk::confBridgeList(std::string room){
    std::string str;
    str.append("Action: ConfbridgeList\r\nConference: ").append(room).append("\r\n\r\n");
    socket->write(str.data(),str.length());
//    ::send(sd,str.data(),str.length(),0);
    return true;

}

bool    Asterisk::confBridgeSayMute (sSubscriber *s){
    std::string str;
    str.append("Action: Originate\r\nChannel: Local/do_playback@cfmc_cdi_private\r\n");
    str.append("Application: Playback\r\nData: ru/admin-mute\r\n");
    str.append("Variable: CfMC_WhoHear=").append(s->channel).append("\r\n\r\n");
//    ::send(sd,str.data(),str.length(),0);
    socket->write(str.data(),str.length());
    return true;
}

bool    Asterisk::confBridgeSayUnMute (sSubscriber *s){
    std::string str;
    str.append("Action: Originate\r\nChannel: Local/do_playback@cfmc_cdi_private\r\n");
    str.append("Application: Playback\r\nData: ru/conf-unmuted\r\n");
    str.append("Variable: CfMC_WhoHear=").append(s->channel).append("\r\n\r\n");
//    ::send(sd,str.data(),str.length(),0);
    socket->write(str.data(),str.length());
    return true;
}

bool    Asterisk::confBridgeMute(sSubscriber *s){
    std::string str;
    str.append("Action: ConfbridgeMute\r\n").append("Conference: ").append(s->conf).append("\r\n");
    str.append("Channel: ").append(s->channel).append("\r\n\r\n");

    str.append("Action: Originate\r\nChannel: Local/do_playback@cfmc_cdi_private\r\n");
    str.append("Application: Playback\r\nData: ru/admin-mute\r\n");
    str.append("Variable: CfMC_WhoHear=").append(s->channel).append("\r\n\r\n");


    socket->write(str.data(),str.length());
//    ::send(sd,str.data(),str.length(),0);
/*
    Timer t;
    t.setTimeout([s](){
        std::string str;
        str.append("Action: Status\r\nChannel: ").append(s->channel).append("\r\n\r\n");
        std::cout<<str;
        ::send(sd,str.data(),str.length(),0);
    },200);
    */
    return true;
}

bool    Asterisk::confBridgeUnMute(sSubscriber *s){
    std::string str;
    str.append("Action: ConfbridgeUnmute\r\n").append("Conference: ").append(s->conf).append("\r\n");
    str.append("Channel: ").append(s->channel).append("\r\n\r\n");

    str.append("Action: Originate\r\nChannel: Local/do_playback@cfmc_cdi_private\r\n");
    str.append("Application: Playback\r\nData: ru/conf-unmuted\r\n");
    str.append("Variable: CfMC_WhoHear=").append(s->channel).append("\r\n\r\n");

    socket->write(str.data(),str.length());
    return true;
}

bool    Asterisk::confBridgeKick (sSubscriber *s){
    std::string str;
    str.append("Action: ConfbridgeKick\r\n").append("Conference: ").append(s->conf).append("\r\n");
    str.append("Channel: ").append(s->channel).append("\r\n\r\n");
    socket->write(str.data(),str.length());
    return true;
}


void    Asterisk::parse(const char * c){

    typedef enum {ROOT,LOGIN,START,STOP,JOIN,LEAVE,LIST_ROOMS,LIST,MUTE,TALKING} PARSER;
    static std::string line="";
//    static bool response_status=false;
    static std::string response_value="";
    static const char *resp_str = "Response: ";
    static const char *auth_str = "Message: Authentication ";
    static const char *conf_start_str = "Event: ConfbridgeStart";
    static const char *conf_end_str = "Event: ConfbridgeEnd";
    static const char *conf_bridge_join = "Event: ConfbridgeJoin";
    static const char *conf_bridge_leave ="Event: ConfbridgeLeave";
    static const char *conf_bridge_list = "Event: ConfbridgeList\r";
    static const char *conf_bridge_list_rooms = "Event: ConfbridgeListRooms";
    static const char *conf_bridge_talking = "Event: ConfbridgeTalking";
    static const char *conf_bridge_mute = "Event: ConfbridgeMute";
    static const char *conf_bridge_unMute = "Event: ConfbridgeUnmute";

    static PARSER parser=ROOT;

//    std::cout << c;
    if (*c=='\n' && line.length()==0) {
        std::cout <<"OOOPS!!!" << std::endl;
        return;
        }

    if (*c=='\n' && line.at(line.length()-1)=='\r'){

        switch (parser){
            case    ROOT:
            if (line.find(resp_str)==0){
 //               response_status=true;
                response_value=line.substr(strlen (resp_str));
//                std::cout<<"GOT RESPONSE!!!!  "<<response_value<<std::endl;
            } else if (line.find(auth_str)==0){
                parser=LOGIN;
                if ((line.substr(strlen (auth_str)).find("accepted"))==0){
                    std::cout<<"GOT AUTH ACCEPTED!!!"<<std::endl;
                    loginState=LOGIN_SUCCESSEFUL;
                    emit onLogin(true);
                    loginTimer->stop();
                    Asterisk::confBridgeListRooms();

                    pingTimer->setInterval(60000);
                    pingTimer->start();

                } else {                                //Some problems with signing in, retrying...
                    std::cout<<"GOT AUTH FAILED!!!"<<std::endl;
                    emit onLogin(false);
                    loginState=LOGIN_FAIL;
                    }

            } else if (line.find(conf_start_str)==0){
                parser=START;
            }else if (line.find(conf_end_str)==0){
                parser=STOP;
            }else if (line.find(conf_bridge_join)==0){
                extractSubscriber("",true);
                parser=JOIN;
            } else if (line.find(conf_bridge_leave)==0){
                parser=LEAVE;
            } else if (line.find(conf_bridge_list_rooms)==0){
                parser=LIST_ROOMS;
                extractRooms(line,true);
            } else if (line.find(conf_bridge_list)==0){
                parser=LIST;
                extractSubscriber("",true);
            } else if (line.find(conf_bridge_mute)==0){
                parser=MUTE;
                extractSubscriber("",true);
                extractSubscriber("Muted: Yes",false);
            } else if (line.find(conf_bridge_unMute)==0){
                parser=MUTE;
                extractSubscriber("",true);
            } else if (line.find(conf_bridge_talking)==0){
                parser=TALKING;
                extractSubscriber("",true);
            }
                break;
            case    LOGIN:
                break;

            case    JOIN:
            case    LEAVE:
            case    LIST:
            case    MUTE:
            case    TALKING:
                Asterisk::extractSubscriber(line,false);
                break;

            case    LIST_ROOMS:
                extractRooms(line,false);
                break;

            case    START:
            case    STOP:
                break;

        }


        if (line=="\r") {

            switch (parser){
            case    ROOT:
                    break;
            case    LOGIN:
                    break;
            case    JOIN:
            case    LIST:
            case    MUTE:
            case    TALKING:
                    emit onSubscriber(REASON::JOIN, Asterisk::extractSubscriber("",false));
                    break;
             case   LEAVE:
                    emit onSubscriber(REASON::LEAVE, Asterisk::extractSubscriber("",false));
                    break;
             case   LIST_ROOMS:
                    break;
             case   START:
             case   STOP:
                    break;
            }

            parser=ROOT;
        }
//        std::cout<<line<<std::endl;
        line="";
    } else {
       line.push_back(*c);
}

}

void        Asterisk::extractRooms(std::string line, bool init){
    static const char *conf_str = "Conference: ";
    static std::string room;
    if (init==true){
        return;
    }

    if (line.find(conf_str)==0){
        substr_test(line,conf_str);
        room=line.substr(strlen(conf_str),line.length()-strlen(conf_str)-1);
        confBridgeList(room);
    }
}

sSubscriber Asterisk::extractSubscriber(std::string line, bool init){
    static sSubscriber subscriber;

    static const char * calleridNum = "CallerIDNum: ";
    static const char * calleridName = "CallerIDName: ";
    static const char * callerAdmin = "Admin: Yes";
    static const char * callerMuted = "Muted: Yes";
    static const char * callerBridgeName = "Conference: ";
    static const char * callerTalking = "TalkingStatus: on";
    static const char * callerChannel = "Channel: ";
    if (init==true){
        subscriber.serverNum=myIndex;
        subscriber.serverName=server.serverName.toStdString();
        subscriber.name="";
        subscriber.number="";
        subscriber.conf="";
        subscriber.channel="";
        subscriber.admin=false;
        subscriber.muted=false;
        subscriber.time=0;
        subscriber.talking=false;
        return subscriber;
    }

    if (line.find(callerBridgeName)==0) {
        substr_test(line,callerBridgeName);
        subscriber.conf=(line.substr(strlen(callerBridgeName),line.length()-strlen(callerBridgeName)-1));}
    if (line.find(calleridNum)==0) {
        substr_test(line,calleridNum);
        subscriber.number=line.substr(strlen(calleridNum), line.length()-strlen(calleridNum)-1);}
    else if (line.find(calleridName)==0){
        substr_test(line,calleridName);
        subscriber.name=line.substr(strlen(calleridName),line.length()-strlen(calleridName)-1);}
    else if (line.find(callerAdmin)==0)
        subscriber.admin=true;
    else if (line.find(callerMuted)==0)
        subscriber.muted=true;
    else if (line.find(callerTalking)==0)
        subscriber.talking=true;
    else if (line.find(callerChannel)==0){
        substr_test(line,callerChannel);
        subscriber.channel=line.substr(strlen(callerChannel),line.length()-strlen(callerChannel)-1);}

   return subscriber;
}

void    Asterisk::substr_test(std::string strin, const char * strtst){
    int strin_length = strin.length();
    int strtst_length = strlen(strtst);
    int out_length=strin_length-strtst_length;

    if (out_length<=0) std::cout << "FIND IT!!!!" << strin << " " <<strtst << std::endl;



}


Asterisk::~Asterisk(){
    logoff();
    pingTimer->stop();
    reconnectTimer->stop();
    loginTimer->stop();

}

