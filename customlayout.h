#ifndef CUSTOMLAYOUT_H
#define CUSTOMLAYOUT_H
#include <QLayout>
#include <QObject>
#include <QVector>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>



typedef struct {
    int                     idx;
    QVariantAnimation*      animation;
    QRect                  rect;
} Animation;




class CustomLayout : public QLayout
{
    Q_OBJECT
    Q_PROPERTY(QRect widgetRect
               READ widgetRect
               WRITE setWidgetRect
               NOTIFY widgetRectChanged)

public:
    CustomLayout();
    ~CustomLayout();

    void addItem(QLayoutItem *) override;
    QLayoutItem *itemAt(int) const override;
    QLayoutItem *takeAt(int) override;
    int count() const override;
    void setGeometry(const QRect &rect) override;
    QSize minimumSize() const override;
    QSize sizeHint() const override;



    void setColumnStretch(int w, int s);


//    void removeWidget(QLayoutItem *);

    QRect widgetRect() const;
    void setWidgetRect(const QRect &value);



private:


    QVector <QLayoutItem*> myItems;
    QMap    <int, QPropertyAnimation*> animation;

    int     maxInLine;
    bool    mDeltaActive;

    void init();

signals:
     void widgetRectChanged(const QRect &value);

};



#endif // CUSTOMLAYOUT_H
