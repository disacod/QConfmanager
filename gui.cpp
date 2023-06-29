
#include "gui.h"
#include "asterisk.h"
#include "room.h"
#include <vector>



static  QVBoxLayout *layout;
static  MainWindow *win;

Gui::~Gui(){

}

Gui::Gui(MainWindow *w)
{

    win=w;
    layout = new QVBoxLayout;

    QWidget *placeholderWidget = new QWidget;

    placeholderWidget->setLayout(layout);

    win->setCentralWidget(placeholderWidget);


    start();
}

void Gui::start(){
    Settings::getServers(&servers);
    asterisk.clear();
    content.clear();

    for (int i=0; i<servers.size();i++){
        asterisk.append( new Asterisk(this));
        asterisk.at(i)->setServer(servers.at(i),i);
        content.append(new ContentProvider(this));
        content.at(i)->setServer(asterisk.at(i));
        content.at(i)->setWindow(win);
        layout->addWidget(content.at(i)->getContentBox());
        asterisk.at(i)->run();
    }

}

void    Gui::stop()
{
    Asterisk *a;
//    ContentProvider *c;

    for (int i=0; i < asterisk.size();i++){
    a=asterisk.at(i);
        a->stop();
    }

}


void    Gui::setSettings(SettingsDialog *s)
{
    mySettings = s;
    connect(mySettings, SIGNAL (onChange()), this, SLOT (doOnChange()));
}

void    Gui::doOnChange(){
    qDebug ("New settings setted");
    stop();
    clearLayout(layout);
    servers.clear();


    start();
}

void Gui::clearLayout(QLayout *layout) {
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}
