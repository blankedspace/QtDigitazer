#ifndef MYSCALER_H
#define MYSCALER_H

#include <QPointF>
#include <QRectF>
#include <QPair>

class MyScaler
{
public:
    MyScaler();


//get дает то, что написано слево от названия функции 

QRectF fileSRectF(){return _fsRect;} //возвращает координаты
QRectF screenRectF(){return _sRect;}
QRect fileSRect(){return fileSRectF().toRect();}
QRect screenRect(){return screenRectF().toRect();}
QPointF getFirstFPoint(){return _fPoints.first;} //F - файл
QPointF getSecondFPoint(){return _fPoints.second;}
QPointF getFirstRPoint(){return _rPoints.first;} //R - реал
QPointF getSecondRPoint(){return _rPoints.second;}

//set - установить значения

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
QPair<QPointF, QPointF> _rPoints; //шаблон классов QPair
QPair<QPointF, QPointF> _fPoints;
QRectF _fsRect;
QRectF _sRect;

//QPointF _rPoint1;
//QPointF _rPoint2;
//QPointF _fPoint1;
//QPointF _fPoint2;

};

#endif // MYSCALER_H
