#ifndef ROOM_H
#define ROOM_H

#include <string>
//#include <vector>
//#include <atomic>
//#include <QPushButton>
#include <QMetaType>
//#include <QLabel>
#include "custombutton.h"



struct sSubscriber {
    int             serverNum;
    std::string     serverName;
    std::string     conf;
    std::string     reserved;
    std::string     number;
    std::string     name;
    std::string     channel;
    uint            time;
    bool            muted;
    bool            admin;
    bool            talking;
    CustomButton    *button;
};

struct  sRoom{
    std::string serverName;
    std::string number;
    std::vector <sSubscriber> subscribers;


};

    enum  REASON {JOIN, LEAVE};
    Q_DECLARE_METATYPE(REASON)
//    Q_DECLARE_METATYPE(sSubscriber)
//class Room
//{

//public:



//    Room();
//    void addRoom(std::string);
//    void addSubscriber(std::string, sSubscriber);
//    void removeRoom(std::string);
/*
    static void pushSubscriber(REASON, sSubscriber);
    static sSubscriber popSubscriber(REASON);
*/

//private:


//    int    findRoom(std::string);
//    int    findSubscriber (int, std::string);

//};


#endif // ROOM_H
