#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QByteArray>
#include <QTimer>


class Notification : public QWidget

{
    Q_OBJECT
    Q_PROPERTY(float popupOpacity READ getPopupOpacity WRITE setPopupOpacity)

    void setPopupOpacity(float opacity);
    float getPopupOpacity() const;

public:
    explicit Notification(QWidget *parent=nullptr);


protected:
    void paintEvent(QPaintEvent *event);

public slots:
    void setPopupText (const QString& text);
    void show();

private slots:
    void hideAnimation();
    void hide();


private:
    QLabel  label;
    QGridLayout layout;
    QPropertyAnimation animation;
    float popupOpacity;
    QTimer *timer;
};

#endif // NOTIFICATION_H
