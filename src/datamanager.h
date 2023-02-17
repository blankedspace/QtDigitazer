#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "dgzgrid.h"
#include "dgzimage.h"

class DataManager
{
public:
    DataManager();

    static DGZGrid* LoadGrid(const QString& filename);
    static QImage* LoadImage(const QString& filename);

    static QImage* GetImage()
    {
        return m_image;
    }
    static DGZGrid* GetGrid()
    {
        return m_grid;
    }

//loadGrid
//loadImage

private:
    static QImage* m_image;
    static DGZGrid* m_grid;
};

#endif // DATAMANAGER_H
