#ifndef DRAWABLEWINDOW_H
#define DRAWABLEWINDOW_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include "dgzgrid.h"
#include "dgzpolyline.h"
#include "dgzscaler.h"
#include "startwindow.h"
#include <QMouseEvent>
#include <QWheelEvent>

class DrawableWindow: public QLabel
{
    Q_OBJECT

public:
    explicit DrawableWindow(QWidget *parent);
    ~DrawableWindow(){}

    enum class DrawingMode{
        ImageNotLoaded,
        ReadyForLinking,
        Set1Point,
        Set2Point,
        SetRealCoord,
        ReadyForDigitizing,
        DigitizingPolyLine,

    };



    double ScaleFactor = 1.2;
    double ShiftFactor = 0.05;
    DrawingMode mode = DrawingMode::ImageNotLoaded;

    DGZPolyline* polyline(){return &p1;}
    StartWindow* m_startWindow;


signals:
    void signalShowTable();
    void signalShowStatusMessage(QString mes);

public slots:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent * event);
protected slots:
    void resizeEvent(QResizeEvent * event);

private:
    QPoint mousePos=QPoint(0,0);
    DGZPolyline p1;
    DGZScaler sc;

    bool mouseMidButton;
    QPointF prevPos;

};


#endif // DRAWABLEWINDOW_H
