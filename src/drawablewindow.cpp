#include "datamanager.h"
#include "drawablewindow.h"
#include <QPainter>

DrawableWindow::DrawableWindow(QWidget *parent)
{
    DGZScaler::instance = &sc;

}

void DrawableWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPen pen;
    pen.setColor(QColor(50,100,0));
    pen.setStyle(Qt::SolidLine);

    //QPointF pt1 = sc.file2Screen(sc.getFirstFPoint());
    QImage* img = DataManager::GetImage();

    if(img)
    p.drawImage(sc.screenRectF(),*img, sc.fileSRectF());

    DGZGrid* grid = DataManager::GetGrid();
    if(grid)
    grid->DrawGird(p,sc);


    pen.setWidth(5);
    p.setPen(pen);

    if(mode == DrawingMode::Set2Point || mode == DrawingMode::SetRealCoord){
    QPointF pt1 = sc.file2Screen(sc.getFirstFPoint());
    p.drawEllipse(pt1,10,10);
    p.drawLine(pt1.x()-5,pt1.y(),pt1.x()+5,pt1.y());
    p.drawLine(pt1.x(),pt1.y()-5,pt1.x(),pt1.y()+5);
    p.drawText(pt1.x()-15,pt1.y()+15,"1");
    }

    if(mode == DrawingMode::SetRealCoord){
    QPointF pt2 = sc.file2Screen(sc.getSecondFPoint());
    p.drawEllipse(pt2,10,10);
    p.drawLine(pt2.x()-5,pt2.y(),pt2.x()+5,pt2.y());
    p.drawLine(pt2.x(),pt2.y()-5,pt2.x(),pt2.y()+5);
    p.drawText(pt2.x()+5,pt2.y()-5,"2");
    }
    else if(mode == DrawingMode::DigitizingPolyLine){
        pen.setColor(QColor(255,15,0));
        pen.setStyle(Qt::DashLine);
        pen.setWidth(1);
        p.setPen(pen);
        for(int i=1; i<p1.size(); i++){
            QPointF pt1 = sc.file2Screen(p1.getPoint(i-1));
            QPointF pt2 = sc.file2Screen(p1.getPoint(i));
            p.drawLine(pt1,pt2);
        }

        pen.setColor(QColor(128,10,0));
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(1);
        p.setPen(pen);
        for(int i=0; i<p1.size(); i++){
            QPointF pt = sc.file2Screen(p1.getPoint(i));
            const int w = 8;
            const int h = 8;
            p.drawRect(int(pt.x()-w/2),int(pt.y()-h/2),w,h);
    }
}}

void DrawableWindow::mouseMoveEvent(QMouseEvent *event)
{

    QString mes = tr("x=%1; y=%2; ").arg(event->x()).arg(event->y());
    QPointF filePoint = sc.screen2File(event->pos());
    mes+=tr("fx=%1; fy=%2; ").arg(filePoint.x()).arg(filePoint.y());

    QPointF realPoint = sc.file2Real(filePoint);
    mes+=tr("rx=%1; ry=%2").arg(realPoint.x()).arg(realPoint.y());
    emit signalShowStatusMessage(mes);
    QPointF curPos = event->position();
    if(mouseMidButton)
    {
        float x = curPos.x() - prevPos.x();
        float y = curPos.y() - prevPos.y();

        QRectF r=DGZScaler::instance->fileSRectF();


        r.setLeft(r.left() - x);
        r.setRight(r.right() - x);
        r.setTop(r.top() - y);
        r.setBottom(r.bottom() - y);
        DGZScaler::instance->setFileSRect(r);

        repaint();
    }
    prevPos = event->position();
}

void DrawableWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MiddleButton)
    {
        mouseMidButton =true;
        prevPos = event->position();
    }
    if(mode == DrawingMode::Set1Point){
        QPoint screenPoint = event->pos();
        QPointF filePoint = sc.screen2File(screenPoint);
        sc.setFirstFPoint(filePoint);
        mode = DrawingMode::Set2Point;
        repaint();
    }
    else if (mode == DrawingMode::Set2Point){
        QPoint screenPoint = event->pos();
        QPointF filePoint = sc.screen2File(screenPoint);
        sc.setSecondFPoint(filePoint);
        mode = DrawingMode::SetRealCoord;

    emit signalShowTable();
    }
    else if(mode==DrawingMode::DigitizingPolyLine){
        if(event->button() == Qt::LeftButton){
        QPoint screenPoint = event->pos();
        QPointF filePoint = sc.screen2File(screenPoint);
        p1.addPoint(filePoint);
        QPointF rp = sc.file2Real(filePoint);
        qDebug() << rp;
    }
        else if(event->button() == Qt::RightButton){
            if(p1.size()>0)p1.removeLastPoint();
        }

        repaint();
    }
}

void DrawableWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MiddleButton)
    {
        mouseMidButton =false;
    }
}

void DrawableWindow::wheelEvent(QWheelEvent *event)
{
    auto delta = event->angleDelta();
    qDebug()<< delta.ry();
    if(delta.ry() > 0)
    {
        m_startWindow->on_zoomin_triggered();
    }
    else
    {
         m_startWindow->on_zoomout_triggered();
    }
}



void DrawableWindow::resizeEvent(QResizeEvent *event)
{
    sc.setScreenRect(QRectF(0,0,width(),height()));
}
