#include "contenprovider.h"



ContentProvider::ContentProvider(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<REASON>();
//    qRegisterMetaType<sSubscriber>();
    win = nullptr;
    myAsterisk=nullptr;
    myBox = new QGroupBox();
    myBoxLayout = new QVBoxLayout();
    myBox->setLayout(myBoxLayout);
    myConfBoxes.clear();

    myCurrentServerStatus = QString::fromUtf8("Нет подключения...");
}

void    ContentProvider::setWindow(MainWindow *w){
    win=w;
}

void ContentProvider::setServer (Asterisk *asterisk){
    myAsterisk = asterisk;
    myBox->setTitle(myAsterisk->getServerName());

    connect(myAsterisk,SIGNAL(onNetworkFail()),this,SLOT(FunctionNetworkFail()));
    connect(myAsterisk,SIGNAL(onLogin(bool)),this, SLOT(FunctionLogin(bool)));
    connect(myAsterisk,SIGNAL(onSubscriber(REASON, sSubscriber)),this, SLOT(FunctionSubscriber(REASON, sSubscriber)));
}

QGroupBox * ContentProvider::getContentBox(){

    return myBox;
}

void ContentProvider::addSubscriber(const sSubscriber &subscriber){
    SETTINGS
    auto it=myConfBoxes.count(subscriber.conf);
    if (it==0){
        ContentProvider::addRoom(&subscriber);
        if (settings.value(SETTINGS_NEW_ROOM).toBool()){
        QString str =QString::fromUtf8("Пользователь  ").append(QString::fromUtf8(subscriber.name.data())).append(": ").append(QString::fromStdString(subscriber.number));
        str.append(QString::fromUtf8("\r\nначал новую конференцию\r\n"));
        str.append(QString::fromUtf8("в комнате ")).append(QString::fromStdString(subscriber.conf));
        win->showNotification(str);
        }

    }

    auto i=myConfBoxes.at(subscriber.conf)->subscribers->count(subscriber.number);

    if (i==0){
        sSubscriber *s = new sSubscriber(subscriber);
        s->button = new PushButton(QString::fromStdString(s->number).append("\r\n").append(QString::fromUtf8(s->name.data())));
        s->button->setObjectName(QString::fromStdString(subscriber.number));


        QPalette pal =s->button->palette();

        pal.setColor(QPalette::Button,QColor(Qt::white));
        QColor col = QColor (Qt::white);
        QString qss = QString ("color: black; background-color: %1").arg(col.name());
        s->button->setStyleSheet(qss);
//        s->button->setAutoDefault(false);
//        s->button->setAutoFillBackground(false);
        s->button->setPalette(pal);
        s->button->update();

        connect(s->button,SIGNAL(clicked()),this,SLOT(buttonClicked()));

        myConfBoxes.at(subscriber.conf)->subscribers->insert(std::pair<std::string,sSubscriber*>(subscriber.number,s));

        myConfBoxes.at(s->conf)->layout->addWidget(s->button);

        if((!settings.value(SETTINGS_NEW_ROOM).toBool() || myConfBoxes.at(s->conf)->subscribers->size()>1) && settings.value(SETTINGS_JOIN_SUBSCRIBER).toBool()){
            QString str =QString::fromUtf8("Пользователь  ").append(QString::fromUtf8(subscriber.name.data())).append(": ").append(QString::fromStdString(subscriber.number));
            str.append(QString::fromUtf8("\r присоединился к беседе\r\n"));
            str.append(QString::fromUtf8("в комнате ")).append(QString::fromStdString(subscriber.conf));
            win->showNotification(str);
        }

    } else {
        //Update subscriber
        myConfBoxes.at(subscriber.conf)->subscribers->at(subscriber.number)->muted=subscriber.muted;

        QPalette pal =myConfBoxes.at(subscriber.conf)->subscribers->at(subscriber.number)->button->palette();
        pal.setColor(QPalette::Button,QColor(Qt::white));
        QString qss = QString ("color: black; background-color: %1").arg(QColor(Qt::white).name());
        if (subscriber.muted==true){
            pal.setColor(QPalette::Button,QColor(Qt::red));
            qss = QString ("background-color: %1").arg(QColor(Qt::red).name());
            myConfBoxes.at(subscriber.conf)->subscribers->at(subscriber.number)->button->setStyleSheet(qss);
            myConfBoxes.at(subscriber.conf)->subscribers->at(subscriber.number)->button->setPalette(pal);
            myConfBoxes.at(subscriber.conf)->subscribers->at(subscriber.number)->button->update();
        } else if (subscriber.talking==true){
            pal.setColor(QPalette::Button,QColor(Qt::green));
            QString qss = QString ("background-color: %1").arg(QColor(Qt::green).name());
            myConfBoxes.at(subscriber.conf)->subscribers->at(subscriber.number)->button->setStyleSheet(qss);
            myConfBoxes.at(subscriber.conf)->subscribers->at(subscriber.number)->button->setPalette(pal);
            myConfBoxes.at(subscriber.conf)->subscribers->at(subscriber.number)->button->update();
        } else {
            myConfBoxes.at(subscriber.conf)->subscribers->at(subscriber.number)->button->setStyleSheet(qss);
            myConfBoxes.at(subscriber.conf)->subscribers->at(subscriber.number)->button->setPalette(pal);
            myConfBoxes.at(subscriber.conf)->subscribers->at(subscriber.number)->button->update();
                }
}


}

void ContentProvider::addRoom(const sSubscriber *s){

    if (myConfBoxes.count(s->conf)==0){

    ConfBox *box = new ConfBox;

    box->box=new QGroupBox(QString::fromUtf8("Конференция: ").append(QString::fromStdString(s->conf)));
    box->layout = new MyLayout;
    box->subscribers = new std::map <std::string, sSubscriber*>;

    box->layout->setColumnStretch(6,0);
    box->layout->setAlignment(Qt::AlignTop);
    box->box->setLayout (box->layout);

    myBoxLayout->addWidget(box->box);

    myConfBoxes.insert(std::pair<std::string, ConfBox*>(s->conf,box));

}
}

void ContentProvider::removeSubscriber(const sSubscriber &subscriber){
    SETTINGS
    if (myConfBoxes.count(subscriber.conf)!=0){
        if (myConfBoxes.at(subscriber.conf)->subscribers->count(subscriber.number)!=0){
            myConfBoxes.at(subscriber.conf)->layout->removeWidget(myConfBoxes.at(subscriber.conf)->subscribers->at(subscriber.number)->button);
            disconnect(myConfBoxes.at(subscriber.conf)->subscribers->at(subscriber.number)->button,SIGNAL(clicked()),this,SLOT(buttonClicked()));
            delete myConfBoxes.at(subscriber.conf)->subscribers->at(subscriber.number)->button;
            myConfBoxes.at(subscriber.conf)->subscribers->erase(myConfBoxes.at(subscriber.conf)->subscribers->find(subscriber.number));
//            myConfBoxes.at(subscriber.conf)->layout->update();
//            myConfBoxes.at(subscriber.conf)->box->update();

            if (settings.value(SETTINGS_EXIT_SUBSCRIBER).toBool()){
            QString str =QString::fromUtf8("Пользователь  ").append(QString::fromUtf8(subscriber.name.data())).append(": ").append(QString::fromStdString(subscriber.number));
            str.append(QString::fromUtf8("\r покинул беседу\r\n"));
            str.append(QString::fromUtf8("в комнате ")).append(QString::fromStdString(subscriber.conf));

            win->showNotification(str);
            }
            if (myConfBoxes.at(subscriber.conf)->subscribers->size()==0)
                removeRoom(subscriber.conf);
        }
    }
}

void ContentProvider::removeRoom(const std::string &r){

    if (myConfBoxes.size()!=0)
    {
        if (myConfBoxes.count(r)!=0){
            if (myConfBoxes.at(r)->subscribers->size()!=0){
                for (auto it=myConfBoxes.at(r)->subscribers->begin(); it!=myConfBoxes.at(r)->subscribers->end();++it){
                    removeSubscriber(*it->second);

                }
            }
                myBoxLayout->removeWidget(myConfBoxes.at(r)->box);

                delete myConfBoxes.at(r)->subscribers;
                delete myConfBoxes.at(r)->layout;
                delete myConfBoxes.at(r)->box;

                myConfBoxes.erase(myConfBoxes.find(r));


        }
    }

}




// PRIVATE SLOTS

void    ContentProvider::FunctionSubscriber(REASON reason, sSubscriber subscriber){
//    sSubscriber subscriber;
    switch (reason){
        case    JOIN:
//            subscriber=Room::popSubscriber(Room::JOIN);
//            std::cout<<"GUI: User action!"<<std::endl;
//            std::cout<<"GUI: "<<subscriber.name<<std::endl;
//            std::cout<<"GUI: "<<subscriber.number<<std::endl;
//            std::cout<<"GUI: "<<subscriber.conf<<std::endl;
//            std::cout<<"GUI: Muted: "<<subscriber.muted<<std::endl;
//            std::cout<<"GUI: Channel: "<<subscriber.channel<<std::endl;
            addSubscriber(subscriber);
            break;

        case    LEAVE:
//           std::cout<<"GUI: Remove user!"<<std::endl;
//           subscriber=Room::popSubscriber(Room::LEAVE);
           removeSubscriber(subscriber);
           break;
    }
}


void    ContentProvider::FunctionLogin(bool login){

    if (login){
    myCurrentServerStatus = QString::fromUtf8("Успешная авторизация!");
//    std::cout<<"Login succsessfull"<<std::endl;
    }
    else {
        myCurrentServerStatus = QString::fromUtf8("Неверный логин или пароль!");
    }

        myBox->setTitle(QString(myAsterisk->getServerName()).append(QString::fromUtf8(" - ")).append(myCurrentServerStatus));
}

void    ContentProvider::FunctionNetworkFail(){
     myCurrentServerStatus = QString::fromUtf8("Сетка поламалась... Пробую снова...");
     myBox->setTitle(QString(myAsterisk->getServerName()).append(QString::fromUtf8(" - ")).append(myCurrentServerStatus));
}

void    ContentProvider::buttonClicked(){
    qDebug("Button clicked");
    PushButton *b =reinterpret_cast<PushButton*>(sender());

    QMenu menu(win);

    QAction mute (QString::fromUtf8("Микрофон Окл./Вкл."),this);
    mute.setObjectName(b->objectName());
    QAction kick (QString::fromUtf8("Удалить участника"),this);
    kick.setObjectName(b->objectName());
    menu.setTitle(QString::fromUtf8("Управление для ").append(b->objectName()));

    menu.addSeparator();
    menu.addAction(&mute);
    menu.addSeparator();
    menu.addAction(&kick);

    connect(&mute,SIGNAL(triggered()),this,SLOT(doMute()));
    connect(&kick,SIGNAL(triggered()),this,SLOT(doKick()));

    menu.exec(QCursor::pos());

}

void    ContentProvider::doKick(){
    QAction *action=reinterpret_cast<QAction*>(sender());
    sSubscriber *subscriber=findSubscriber(action->objectName());
    if (subscriber==nullptr) return;
    myAsterisk->confBridgeKick(subscriber);

}

void    ContentProvider::doMute (){
    QAction *action=reinterpret_cast<QAction*>(sender());
    sSubscriber *subscriber=findSubscriber(action->objectName());
    if (subscriber==nullptr) return;
    if (subscriber->muted) {
        myAsterisk->confBridgeUnMute(subscriber);

    }
        else {
        myAsterisk->confBridgeMute(subscriber);

        }
}

sSubscriber* ContentProvider::findSubscriber(QString s){

    for (std::map <std::string, ConfBox*>::iterator it=myConfBoxes.begin();it!=myConfBoxes.end();it++){
        if (it->second->subscribers->count(s.toStdString())>0){
            return it->second->subscribers->at(s.toStdString());

        }
    }
    return nullptr;
}
