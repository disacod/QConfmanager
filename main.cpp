#include "mainwindow.h"
#include "gui.h"
//#include "room.h"
//#include "asterisk.h"
//#include <iostream>
#include <QApplication>
//#include <QVBoxLayout>
//#include <QPushButton>
//#include <QGroupBox>
#include <QString>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QMessageBox>
#include <QDebug>
//#include <vector>
#include <QDate>






int main(int argc, char *argv[])
{

    static const std::string hide_cmd="tray";
    qDebug("Starting app");
    QApplication a(argc, argv);
//    Settings    settings;

    QSystemSemaphore semaphore("asteriskconfmon_sem", 1);  // создаём семафор
    semaphore.acquire(); // Поднимаем семафор, запрещая другим экземплярам работать с разделяемой памятью

#ifdef WIN64
    // в linux/unix разделяемая память не освобождается при аварийном завершении приложения,
    // поэтому необходимо избавиться от данного мусора
    QSharedMemory nix_fix_shared_memory("asteriskconfmon");
    if(nix_fix_shared_memory.attach()){
        nix_fix_shared_memory.detach();
    }
#endif

    QSharedMemory sharedMemory("asteriskconfmon");  // Создаём экземпляр разделяемой памяти
    bool is_running;            // переменную для проверки ууже запущенного приложения
    if (sharedMemory.attach()){ // пытаемся присоединить экземпляр разделяемой памяти
                                // к уже существующему сегменту
        is_running = true;      // Если успешно, то определяем, что уже есть запущенный экземпляр
    }else{
        sharedMemory.create(1); // В противном случае выделяем 1 байт памяти
        is_running = false;     // И определяем, что других экземпляров не запущено
    }
    semaphore.release();        // Опускаем семафор


    if(is_running){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(QString::fromUtf8("Приложение уже запущено.\n"
                        "Вы можете запустить только один экземпляр приложения."));
        msgBox.exec();
        return 1;
    }

/*
    QDate date;
    date=QDate::currentDate();

    if (date>QDate(2022,12,31)) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(QString::fromUtf8("Системный сбой.\n"
                        "Обратитесь к разработчику."));
        msgBox.exec();
        return 1;

    }
*/


    a.setQuitOnLastWindowClosed(false);
    SettingsDialog *settings = new SettingsDialog(nullptr);
    MainWindow w;
    w.setSettings(settings);
    Gui gui(&w);
    gui.setSettings(settings);


    w.show();

    for (int i=0;i<argc;i++){
        if (hide_cmd.find(argv[i])==0) w.tray();
    }

    return a.exec();
}

