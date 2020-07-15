#include "citygraphicsview.h"
#include <QDebug>
#include <qmath.h>
CityGraphicsView::CityGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    // do i need those setups?
    // !!! 13 is must-have!
    CityGraphicsView::setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    CityGraphicsView::setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameStyle(0);
    setRenderHint(QPainter::Antialiasing,true);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    setViewportUpdateMode(QGraphicsView::ViewportUpdateMode::FullViewportUpdate);
    //setTransformationAnchor(QGraphicsView::AnchorUnderMouse); //stopped working for some reason...
    setMouseTracking(true);

}

CityGraphicsView::CityGraphicsView()
{

}

void CityGraphicsView::wheelEvent(QWheelEvent *event)
{
    auto t = transform(); // horizontal scaling is equal to vertical scaling
    int rot = event->delta();
    if ( (t.m11()>=zoom_max && rot > 0 ) || ( t.m11()<=zoom_min && rot < 0 ))
    {
        return;
    }else
    {

        rot > 0 ? scale(1.1,1.1) : scale(0.9,0.9);
        auto new_transform = transform();
        if (new_transform.m11()>zoom_max)
        {
            resetTransform();
            scale(zoom_max,zoom_max);
        }else if(new_transform.m11()<zoom_min)
        {
            resetTransform();
            scale(zoom_min,zoom_min);
        }
        emit scale_changed_event(QString::number(transform().m11()));
    }
    event->accept();
}



void CityGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QString rrr = "r move detected![ %1 ; %2 ]";
    qDebug() << rrr;
    emit mouse_moved(event);
    if (event->buttons() & Qt::MouseButton::LeftButton)
    {

        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - click_x0));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - click_y0));
        click_x0 = event->x();
        click_y0 = event->y();
        event->accept();

    }else
    {
        event->ignore();
    }
}

void CityGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        setCursor(Qt::ClosedHandCursor);
        click_x0 = event->x();
        click_y0 = event->y();
        event->accept();
        QString rrr = "r click![ %1 ; %2 ]";
        qDebug() << rrr.arg(click_x0).arg(click_y0);
    }else
    {
        event->ignore();
    }

}

void CityGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        setCursor(Qt::CursorShape::ArrowCursor);
        QString rrr = "r release![ %1 ; %2 ]";
        qDebug() << rrr;
        event->accept();
    }else
    {
        event->ignore();
    }
}






