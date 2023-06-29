#include "custombutton.h"

CustomButton::CustomButton(const QString& text, QWidget* parent) : QLabel (parent)
{
    myText = QString (text);
    timer = new QTimer(this);
    currentTime = 0;
    setText(text+QString::fromUtf8("\r\n").append(timeToString()));

//    setMaximumHeight(40);
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setAlignment(Qt::AlignCenter);
    setLineWidth(2);
    adjustSize();


//    QSize size(this->size());
//    setMinimumSize(size);


    startTimer();
}

CustomButton::~CustomButton(){
    timer->stop();
    delete timer;


}

void CustomButton::startTimer(){


    timer->setInterval(1000);
    connect(timer,SIGNAL (timeout()), this,SLOT (incTimer()));
    timer->start();

}

void CustomButton::incTimer(){
    currentTime++;
    update();
}


void CustomButton::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev)
    emit clicked();
}

void CustomButton::paintEvent(QPaintEvent *ev)
{
    setText(myText+QString::fromUtf8("\r\n").append(timeToString()));
     QLabel::paintEvent(ev);
}

QString CustomButton::timeToString(){
    QString str_m=QString::number(currentTime%60);
    QString str_s=QString::number(currentTime/60);

    return str_s.append(QString::fromUtf8(":").append(str_m));

}

void CustomButton::setGeometry(const QRect *r)
{
    Q_UNUSED(r)
};
