#ifndef CITYGRAPHICSSCENE_H
#define CITYGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsItem>
#include <QDebug>
#include "citygraphicsitem.h"
class CityGraphicsScene : public QGraphicsScene
{
public:
    CityGraphicsScene();
    void prepare_entities(); // filler for db reading

    public slots:
    void on_zoom_changed(const QString &_zoom);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
private:
    QBrush background_brush;
    qreal scene_width = 1024;
    qreal scene_height = 1024;
    int power_of_2 = 1;
    QVector<CityGraphicsItem *> graphic_items= {};
    QVector<QString> names_filler = {"Moscow", 	"Saint Petersburg","Novosibirsk","Yekaterinburg",
                                     "Nizhny","Kazan","Chelyabinsk","Omsk","Samara"," 	"
                                     "Rostov-on-Don"};  // filler for db reading
    CityGraphicsItem *test_item; // test item
};

#endif // CITYGRAPHICSSCENE_H
