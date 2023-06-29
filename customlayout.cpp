#include "customlayout.h"
#include "custombutton.h"
#include <QObject>

CustomLayout::CustomLayout()
{
        maxInLine = 5;
        init();
}

CustomLayout::~CustomLayout(){
    QLayoutItem *item;
    while ((item = takeAt(0))) {
        delete item;
    }

}

void CustomLayout::init(){

    myItems.clear();
    animation.clear();

}

QLayoutItem *CustomLayout::itemAt(int idx) const{

    return myItems.value(idx);
}

QLayoutItem *CustomLayout::takeAt(int idx){

    QLayoutItem *item = idx >= 0 && idx < myItems.size() ? myItems.takeAt(idx) : 0;

    return item;
}

void CustomLayout::addItem(QLayoutItem *item){
    myItems.append(item);
//    int idx = myItems.size()-1;

}

int CustomLayout::count() const {
    return myItems.size();
}

void CustomLayout::setGeometry(const QRect &rect){

    if (myItems.size()==0) return;

    int counts = myItems.size();

    int mod=maxInLine;

    int w = rect.width()/(mod);
    int h = myItems.at(0)->widget()->geometry().height();


    int i=0;
//    int last_h=0;
    while (i<counts) {

          QRect geom (rect.x()+((i % maxInLine))*w,rect.y()+(i/maxInLine)*h,w,h);
//          last_h=geom.y() + geom.height();
          if (myItems.at(i)->widget()->geometry()!=geom)
          {
//              QWidget *b = myItems.at(i)->widget();
                QPropertyAnimation *a = new QPropertyAnimation(myItems.at(i)->widget(),"geometry");
                a->setDuration(400);
                a->setStartValue(myItems.at(i)->widget()->geometry());
                a->setEndValue(geom);
                a->start();

//              a->deleteLater();
           //   myItems.at(i)->setGeometry(geom);
          }
          ++i;
    }

}


QSize CustomLayout::sizeHint() const
{
    QSize s(0,0);
    int n = myItems.size();
    if (n > 0) s = QSize(300,60);
    int i = 0;
    while (i<n) {
        QLayoutItem *item = myItems.at(i);
        s=s.expandedTo(item->sizeHint());
        ++i;
    }
    return s;
}

QSize CustomLayout::minimumSize() const
{
    QSize s(600,50);

    if (myItems.size()!=0) s.setHeight(myItems.last()->geometry().y()+26);
    return s;
}

void CustomLayout::setColumnStretch(int w, int s)
{
    Q_UNUSED(s)
    maxInLine=w;
}


QRect CustomLayout::widgetRect() const
{
//    if (item)
//        return item->geometry();
    return QRect();
}

void CustomLayout::setWidgetRect(const QRect &value)
{
    Q_UNUSED(value)
}

