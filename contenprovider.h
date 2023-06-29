#ifndef CONTENPROVIDER_H
#define CONTENPROVIDER_H

#include <QObject>
#include <QLayout>
#include <QGroupBox>
#include <QAction>
#include <QMenu>
#include <custombutton.h>

#include "asterisk.h"
#include "mainwindow.h"
#include "customlayout.h"
//#include "animlayout.h"


#define PushButton CustomButton
#define MyLayout    CustomLayout

struct ConfBox {
    QGroupBox *box;
//    QGridLayout *layout;
    MyLayout *layout;
    std::map <std::string, sSubscriber*> *subscribers;
};

class ContentProvider : public QObject
{
    Q_OBJECT
public:
    explicit    ContentProvider(QObject *parent);
    void        setServer (Asterisk *);
    void        setWindow (MainWindow *);
    QGroupBox * getContentBox ();




private:
    MainWindow  *win;
    QString     myCurrentServerStatus;

    std::map    <std::string, ConfBox*> myConfBoxes;
    QGroupBox   *myBox;
    QVBoxLayout *myBoxLayout;
    Asterisk    *myAsterisk;


    void        addSubscriber(const sSubscriber &subscriber);
    void        addRoom(const sSubscriber *s);
    void        removeSubscriber(const sSubscriber &subscriber);
    void        removeRoom(const std::string &r);
    sSubscriber* findSubscriber(QString s);

private slots:
    void        FunctionSubscriber(REASON,sSubscriber s);
    void        FunctionLogin(bool);
    void        FunctionNetworkFail();
    void        buttonClicked();
    void        doKick();
    void        doMute();


signals:

};

#endif // CONTENPROVIDER_H
