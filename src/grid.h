#ifndef GRID_H
#define GRID_H

#include <QVector>
class Grid
{
public:
    //задаем начальные значения для расположения грида и сам грид
    Grid();
    QVector<float> values;

    int xSize = 0;
    int ySize = 0;
    float maxValue = 0;
};

#endif // GRID_H
