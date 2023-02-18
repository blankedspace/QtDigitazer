#include "dgzscaler.h"


DGZScaler* DGZScaler::instance = nullptr;

DGZScaler::DGZScaler()
{

    setFileSRect(QRectF(0,0,100,100));
    setScreenRect(QRectF(0,0,100,100));
}

QPointF DGZScaler::screen2File(QPointF pt)
{

    double xf1 = _fsRect.left(); 
    double xf2 = _fsRect.right();
    double xs1 = _sRect.left();
    double xs2 = _sRect.right();
    double yf1 = _fsRect.bottom();
    double yf2 = _fsRect.top();
    double ys1 = _sRect.bottom();
    double ys2 = _sRect.top();
    double xs = pt.x();
    double ys = pt.y();

    QPointF fpt;
    fpt.setX(xf1+(xs-xs1)/(xs2-xs1)*(xf2-xf1));
    fpt.setY(yf1+(ys-ys1)/(ys2-ys1)*(yf2-yf1));
    return fpt;
}

QPointF DGZScaler::file2Screen(QPointF pt)
{
    return file2Screen(_fsRect,pt);
}

QPointF DGZScaler::file2Screen(QRectF file,QPointF pt)
{

    double xf1 = file.left();
    double xf2 = file.right();
    double xs1 = _sRect.left();
    double xs2 = _sRect.right();
    double yf1 = file.bottom();
    double yf2 = file.top();
    double ys1 = _sRect.bottom();
    double ys2 = _sRect.top();
    double xf = pt.x();
    double yf = pt.y();

    QPointF spt;
    spt.setX(xs1+(xf-xf1)/(xf2-xf1)*(xs2-xs1));
    spt.setY(ys1+(yf-yf1)/(yf2-yf1)*(ys2-ys1));
    return spt;
}
QPointF DGZScaler::real2File(QPointF pt)
{

    double xf1 = _fPoints.first.x();
    double yf1 = _fPoints.first.y();
    double xf2 = _fPoints.second.x();
    double yf2 = _fPoints.second.y();
    double xr1 = _rPoints.first.x();
    double yr1 = _rPoints.first.y();
    double xr2 = _rPoints.second.x();
    double yr2 = _rPoints.second.y();
    double xr = pt.x();
    double yr = pt.y();

    QPointF fpt;
    fpt.setX(xf1+(xr-xr1)/(xr2-xr1)*(xf2-xf1));
    fpt.setY(yf1+(yr-yr1)/(yr2-yr1)*(yf2-yf1));
    return fpt;
}

QPointF DGZScaler::file2Real(QPointF pt)
{

    double xf1 = _fPoints.first.x();
    double yf1 = _fPoints.first.y();
    double xf2 = _fPoints.second.x();
    double yf2 = _fPoints.second.y();
    double xr1 = _rPoints.first.x();
    double yr1 = _rPoints.first.y();
    double xr2 = _rPoints.second.x();
    double yr2 = _rPoints.second.y();
    double xf = pt.x();
    double yf = pt.y();

    QPointF rpt;
    rpt.setX(xr1+(xf-xf1)/(xf2-xf1)*(xr2-xr1));
    rpt.setY(yr1+(yf-yf1)/(yf2-yf1)*(yr2-yr1));
    return rpt;
}

