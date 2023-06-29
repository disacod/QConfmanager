#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QObject>
#include <QLabel>
#include <QTimer>

class CustomButton : public QLabel
{
    Q_OBJECT
public:
    explicit CustomButton( const QString& text="", QWidget* parent=0 );
    ~CustomButton();

    void setGeometry(const QRect *r);


signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *) override;




private:
    QString myText;
    QTimer   *timer;
    int     currentTime;

    QString   timeToString();
    void        startTimer();



private slots:
    void    incTimer();

};

#endif // CUSTOMBUTTON_H
