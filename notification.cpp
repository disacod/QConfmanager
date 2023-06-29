#include "notification.h"
#include <QPainter>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>



Notification::Notification(QWidget *parent) :QWidget (parent)

{
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint|Qt::WindowStaysOnTopHint|Qt::Popup);

    setAttribute(Qt::WA_TranslucentBackground);     // Indicates that the background will be transparent
    setAttribute(Qt::WA_ShowWithoutActivating);     // At the show, the widget does not get the focus automatically

    animation.setTargetObject(this);                // Set the target animation
    animation.setPropertyName("popupOpacity");      //
    connect(&animation, SIGNAL (finished()), this, SLOT(hide()));

    label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label.setStyleSheet("QLabel { color : white; "
                        "margin-top: 6px;"
                        "margin-bottom: 6px;"
                        "margin-left: 10px;"
                        "margin-right: 10px; }");

    layout.addWidget(&label, 0, 0);
    setLayout(&layout);

    timer = new QTimer();
    connect(timer, SIGNAL (timeout()), this, SLOT (hideAnimation()));

}

void Notification::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect roundedRect;
    roundedRect.setX(rect().x() + 5);
    roundedRect.setY(rect().y() + 5);
    roundedRect.setWidth(rect().width() - 10);
    roundedRect.setHeight(rect().height() - 10);

    painter.setBrush(QBrush(QColor(0,0,0,180)));
    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(roundedRect, 10, 10);
}

void Notification::setPopupText(const QString &text)
{
    label.setText(text);    // Set the text in the Label
    adjustSize();           // With the recalculation notice sizes
}

void Notification::show()
{
    setWindowOpacity(0.0);  // Set the transparency to zero

    animation.setDuration(150);     // Configuring the duration of the animation
    animation.setStartValue(0.0);   // The start value is 0 (fully transparent widget)
    animation.setEndValue(1.0);     // End - completely opaque widget


    QScreen *screen = QApplication::primaryScreen();
    QRect geom = screen->availableGeometry();


    setGeometry(geom.x() - 36 - width() + geom.x(),
                geom.height() - 36 - height() + geom.y(),
                width(),
                height());

//    setGeometry(QGuiApplication::primaryScreen())

    QWidget::show();

    animation.start();
    timer->start(4000);
}

void Notification::hideAnimation()
{
    timer->stop();
    animation.setDuration(1000);
    animation.setStartValue(1.0);
    animation.setEndValue(0.0);
    animation.start();
}

void Notification::hide()
{
    // If the widget is transparent, then hide it
    if(getPopupOpacity() == 0.0){
        QWidget::hide();
    }
}

void Notification::setPopupOpacity(float opacity)
{
    popupOpacity = opacity;

    setWindowOpacity(opacity);
}

float Notification::getPopupOpacity() const
{
    return popupOpacity;
}
