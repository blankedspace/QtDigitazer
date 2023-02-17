#ifndef DGZIMAGE_H
#define DGZIMAGE_H

#include <QImage>



class DGZImage
{
public:
    DGZImage();
    bool load(const QString& filename);
private:
    QImage m_image;
};

#endif // DGZIMAGE_H
