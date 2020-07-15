#ifndef CITYGRAPHICSVIEW_H
#define CITYGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <citygraphicsscene.h>
#include <QGraphicsItem>
#include <QScrollBar>
class CityGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    CityGraphicsView(QWidget *parent = nullptr);
    CityGraphicsView();
signals:
    void scale_changed_event(const QString &new_scale);
    void mouse_moved(const QMouseEvent *event);

private:
    // zoom vars
    qreal zoom_max = 5.0;
    qreal zoom_min = 0.5;

    // drag / check coords vars
    int click_x0 = 0;
    int click_y0 = 0;

protected:
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // CITYGRAPHICSVIEW_H
