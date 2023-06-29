//#include "room.h"
//#include <QString>

//    static std::vector <sRoom> rooms;
/*
    static std::vector <sSubscriber*> subscribersJoin;
    static std::vector <sSubscriber*> subscribersLeave;
*/
//Room::Room()
//{

//}
/*
void Room::pushSubscriber(REASON reason,sSubscriber subscriber){
 //   std::vector <sSubscriber*> subscribers;
    switch (reason){
        case    JOIN:
        subscribersJoin.push_back(new sSubscriber(subscriber));
            break;
    case    LEAVE:
        subscribersLeave.push_back(new sSubscriber(subscriber));
        break;
    }

}

sSubscriber Room::popSubscriber(REASON reason) {
//    std::vector <sSubscriber*> subscribers;
    sSubscriber s;
    switch (reason){
        case    JOIN:
        s=*subscribersJoin.at(0);
        delete subscribersJoin.at(0);
        subscribersJoin.erase(subscribersJoin.begin());
            break;
    case    LEAVE:
        s=*subscribersLeave.at(0);
        delete subscribersLeave.at(0);
        subscribersLeave.erase(subscribersLeave.begin());
        break;
    }
    return s;
}
*/
