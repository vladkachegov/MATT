#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "citygraphicsitem.h"
#include "citygraphicsscene.h"
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CityGraphicsView *view = ui->gv;

    CityGraphicsScene *scene = new CityGraphicsScene(); // add parent constructor later
    connect(view, &CityGraphicsView::scale_changed_event, ui->scale_text, &QLineEdit::setText);
    connect(view, &CityGraphicsView::scale_changed_event, scene, &CityGraphicsScene::on_zoom_changed);
    connect(view,&CityGraphicsView::mouse_moved,[=](const QMouseEvent *event)
    {
        auto event_pos_rel = event->pos();
        auto event_pos_abs = view->mapToScene(event_pos_rel);
        qreal x_abs = event_pos_abs.x();
        qreal y_abs = event_pos_abs.y();
        ui->x_text->setText(QString::number(x_abs));
        ui->y_text->setText(QString::number(y_abs));
    }
    );
    scene->prepare_entities();
    view->setScene(scene);
    view->fitInView(0,0,1024,1024,Qt::AspectRatioMode::KeepAspectRatio);
    view->setBackgroundBrush(QBrush(Qt::cyan, Qt::SolidPattern));

}

MainWindow::~MainWindow()
{
    delete ui;
}



