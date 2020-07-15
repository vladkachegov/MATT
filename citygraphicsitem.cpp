#include "citygraphicsitem.h"
#include <QPainter>
#include <QDebug>
CityGraphicsItem::CityGraphicsItem()
{
    setFlag(QGraphicsItem::GraphicsItemFlag::ItemIgnoresTransformations);
}

CityGraphicsItem::CityGraphicsItem(QString cityName, int minLevel, int maxLevel, int displayPriority):
    city_name(cityName),min_level(minLevel),max_level(maxLevel),display_priority(displayPriority)
{
    setFlag(QGraphicsItem::GraphicsItemFlag::ItemIgnoresTransformations);
}

QRectF CityGraphicsItem::boundingRect() const
{    

    return QRectF(aleft,atop,height,width);
    return QRectF(-50,-50,200,200);
}
QPainterPath CityGraphicsItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    path.addRect(text_rect);
    return path;
}

void CityGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    auto metrix = painter->fontMetrics();
    int width = metrix.width(city_name); // tbd
    int height = metrix.height();
    text_rect = QRect(text_aleft,text_atop - height,
                      width,height);
    painter->drawRect(text_aleft,text_atop - height,width,height);

    auto coll_items = collidingItems();
    if (coll_items.size()>0) // let's assume there could be only ONE collision!!!!!
    {
        auto coll_item = dynamic_cast<CityGraphicsItem*>(coll_items.at(0));
        if (coll_item->display_priority >= this->display_priority)
        {
            painter->drawEllipse(0,0,10,10);
        }else
        {
            coll_item->hide_city_name();
            painter->drawEllipse(0,0,10,10);
            painter->drawText(text_aleft,text_atop - height,width,height,0,city_name);
        }
        colliding_items = coll_items;
    }else
    {
        foreach (auto elem,colliding_items)
        {
            auto coll_item = dynamic_cast<CityGraphicsItem*>(elem);
            coll_item->show_city_name();
        }
        painter->drawEllipse(0,0,10,10);
        painter->drawText(text_aleft,text_atop - height,width,height,0,city_name);
        this->setVisible(true);
    }
}

void CityGraphicsItem::hide_city_name()
{
    forsed_to_hide = true;
    this->hide();
}

void CityGraphicsItem::show_city_name()
{
    forsed_to_hide = false;
    this->show();
}

void CityGraphicsItem::set_city_name(const QString &value)
{
    city_name = value;
}

QString CityGraphicsItem::get_city_name() const
{
    return city_name;
}

void CityGraphicsItem::react_to_zoom(const qreal &zoom)
{
        zoom_value = zoom;
        auto collidingElements = collidingItems();
        if (zoom > max_level || zoom < min_level)
        {
            setVisible(false);

        }else
        {
            setVisible(!forsed_to_hide);
        }
}

bool CityGraphicsItem::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    auto projected_shape = mapToItem(other,shape());
    auto br_proj = projected_shape.boundingRect(); // brojected rect
    auto br_abs = other->shape().boundingRect();
    br_proj.setWidth(br_proj.width()/zoom_value);
    br_proj.setHeight(br_proj.height()/zoom_value);
    br_abs.setWidth(br_abs.width()/zoom_value);
    br_abs.setHeight(br_abs.height()/zoom_value);
    if (br_proj.intersects(br_abs))
    {
        return true;
    }else
    {
        return false;
    }

}


