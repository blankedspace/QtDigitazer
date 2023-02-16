#ifndef MYPOLYLINE_H
#define MYPOLYLINE_H
#include <QVector>
#include <QPointF>
#include <QPen>

class MyPolyline
{
public:
    MyPolyline(); //конструктор. если функция называется как класс, то это конструктор

    void clear(){_points.clear();} //void - значит ничо не возвращает
    void addPoint(QPointF pt){_points.push_back(pt);} //после точки мы используем функции класса
    void removeLastPoint(){_points.pop_back();}
    void removePoint(int i){_points.removeAt(i);}
    void insertPoint(int i,QPointF pt){_points.insert(i,pt);} //вставить точку
    QPointF getPoint(int i){return _points[i];}
    int size(){return _points.size();}

    void setPen(QPen p){_pen = p;}
    QPen getPen(){return _pen;}

private:
    QVector<QPointF> _points; //массив (шаблон) классов QPointF (внутрь мы вставили, какие данные там хранятся)

    QPen _pen; //объявляем объект 
};

#endif // MYPOLYLINE_H
