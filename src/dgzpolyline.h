#ifndef DGZPOLYLINE_H
#define DGZPOLYLINE_H
#include <QVector>
#include <QPointF>
#include <QPen>

class DGZPolyline
{
public:
    DGZPolyline();

    void clear(){_points.clear();}
    void addPoint(QPointF pt){_points.push_back(pt);}
    void removeLastPoint(){_points.pop_back();}
    void removePoint(int i){_points.removeAt(i);}
    void insertPoint(int i,QPointF pt){_points.insert(i,pt);}
    QPointF getPoint(int i){return _points[i];}
    int size(){return _points.size();}

    void setPen(QPen p){_pen = p;}
    QPen getPen(){return _pen;}

private:
    QVector<QPointF> _points;

    QPen _pen;
};

#endif // DGZPOLYLINE_H
