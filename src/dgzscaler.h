#ifndef DGZSCALER_H
#define DGZSCALER_H

#include <QPointF>
#include <QRectF>
#include <QPair>

class DGZScaler
{
public:
    DGZScaler();



QRectF fileSRectF(){return _fsRect;}
QRectF screenRectF(){return _sRect;}
QRect fileSRect(){return fileSRectF().toRect();}
QRect screenRect(){return screenRectF().toRect();}
QPointF getFirstFPoint(){return _fPoints.first;}
QPointF getSecondFPoint(){return _fPoints.second;}
QPointF getFirstRPoint(){return _rPoints.first;}
QPointF getSecondRPoint(){return _rPoints.second;}

void setFileSRect(QRectF r){_fsRect = r;}
void setScreenRect(QRectF r){_sRect = r;}
void setFirstFPoint(QPointF pt){_fPoints.first = pt;}
void setSecondFPoint(QPointF pt){_fPoints.second = pt;}
void setFirstRPoint(QPointF pt){_rPoints.first = pt;}
void setSecondRPoint(QPointF pt){_rPoints.second = pt;}

QPointF screen2File(QPointF pt);
QPointF screen2File(QPoint pt){return screen2File(QPointF(pt));}

QPointF file2Screen(QPointF pt);

QPointF real2File(QPointF pt);
QPointF file2Real(QPointF pt);

private:
QPair<QPointF, QPointF> _rPoints;
QPair<QPointF, QPointF> _fPoints;
QRectF _fsRect;
QRectF _sRect;


};

#endif // DGZSCALER_H
