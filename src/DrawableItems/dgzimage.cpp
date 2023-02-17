#include "dgzimage.h"

DGZImage::DGZImage():
    m_image()
{

}

bool DGZImage::load(const QString &filename)
{
    bool ok = m_image.load(filename);
    return ok;
}
