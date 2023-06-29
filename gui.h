#ifndef GUI_H
#define GUI_H

#include "mainwindow.h"
#include "asterisk.h"
#include "contenprovider.h"
//#include "notification.h"
//#include <QString>
//#include <QSignalMapper>
//#include <QMenu>
//#include <QAction>
#include "settings.h"


namespace Ui {
class Gui;
}

class Gui : public QObject
{

    Q_OBJECT

public:
    explicit Gui(MainWindow*);

    ~Gui();
    void start();
    void stop();
    void setSettings(SettingsDialog *);

public slots:
    void doOnChange();

private:
    void clearLayout(QLayout *layout);

    SettingsDialog *mySettings;
    QVector <Asterisk*> asterisk;
    QVector <ContentProvider*> content;
    QList<Server> servers;
};

#endif // GUI_H
