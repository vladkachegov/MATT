#include "citygraphicsscene.h"
#include <QPainter>
CityGraphicsScene::CityGraphicsScene()
{
    this->setSceneRect(0,0,scene_width,scene_height);
    setBackgroundBrush(QBrush(Qt::red));
}

void CityGraphicsScene::prepare_entities()
{
    for (int ii = 100;ii<scene_width;ii+=100)
    {
        CityGraphicsItem *item = new CityGraphicsItem();
        item->set_city_name(names_filler.at(ii/100 -1));
        item->setPos(ii,ii);
        addItem(item);
        graphic_items.push_back(item);
    }
    test_item = new CityGraphicsItem("FILLER TEST CITY!",1,5,3);

    test_item->setPos(520,500);
    addItem(test_item);
    graphic_items.push_back(test_item);
}

void CityGraphicsScene::on_zoom_changed(const QString &_zoom)
{
    qDebug() << "reacting to zoom";
    double zoom = _zoom.toDouble();
    foreach(auto item, graphic_items)
    {
        item->react_to_zoom(zoom);
    }
}

void CityGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    // why paint objects in this method?
}




void CityGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

    auto arr = test_item->collidingItems();
    int size = arr.size();
    qDebug() << "doubleclick! size = " << size;
}
