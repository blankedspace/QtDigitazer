#include "dgzgrid.h"


DGZGrid::DGZGrid()
{

}

void DGZGrid::DrawGird(QPainter& p,DGZScaler& sc)
{
    QPen pen;

    pen.setColor(QColor(50,0,0));
    pen.setStyle(Qt::SolidLine);

    pen.setWidth(1000*( xSize/(sc.fileSRectF().width())));
    p.setPen(pen);

    if( values.size() != 0)
    {
        for (int i = 0; i <  xSize; ++i) {
            for (int j = 0; j <  ySize; ++j) {
                QPointF point( xSize*10 - i*10,j*10);
                QPointF pt1 = sc.file2Screen(point);
                float data =  ( values[i+j* xSize]/ maxValue);
                pen.setColor(QColor(data*222,data*222,data*222));

                p.setPen(pen);
                p.drawPoint(pt1);

            }
        }
    }

}
