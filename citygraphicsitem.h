#ifndef CITYGRAPHICSITEM_H
#define CITYGRAPHICSITEM_H

#include <QObject>
#include <qgraphicsitem.h>
#include <QGraphicsTextItem>
#include <QTextItem>
class CityGraphicsItem : public QGraphicsItem
{

public:
    CityGraphicsItem();
    CityGraphicsItem(QString cityName, int min_level, int max_level, int displayPriority);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void hide_city_name();
    void show_city_name();
    void set_city_name(const QString &value);
    QString get_city_name() const;
    void react_to_zoom(const qreal &zoom);
    QPainterPath shape() const override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;

private:
    //vision properties
    qreal zoom_value = 1;
    bool forsed_to_hide = false;
    QList<QGraphicsItem*> colliding_items = {};
    // item properties
    int min_level = 0;
    int max_level = 5;
    int display_priority = 0;
    qreal width = 10;
    qreal height = 10;
    qreal aleft = -width/2;
    qreal atop = -height/2;

    // text properties
    qreal text_atop = atop - 2;
    qreal text_aleft = aleft + width;
    QRect text_rect;
    QString city_name = "Moscow";

};

#endif // CITYGRAPHICSITEM_H
