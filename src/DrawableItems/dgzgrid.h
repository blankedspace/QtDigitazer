#ifndef DGZGRID_H
#define DGZGRID_H

#include <QVector>
#include <QPainter>

#include "dgzscaler.h"

class DGZGrid
{
public:
    void DrawGird(QPainter& p,DGZScaler& sc);
    DGZGrid();
    QVector<float> values;

    int xSize = 0;
    int ySize = 0;
    float maxValue = 0;

    QRectF rect;

};

#endif // DGZGRID_H
