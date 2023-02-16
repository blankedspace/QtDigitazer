#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPen> //включаем классы Qt
#include <QBrush> 
#include <QColor>
#include <QPainter>
#include <QMouseEvent>
#include "myscaler.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include "grid.h"
#include <mypolyline.h>


//заголовочные файлы нужны для того, чтобы основные файлы не были перегружены. В заголовочных мы только объявляем 
namespace Ui { //поле имён
class MainWindow;
}

class MainWindow : public QMainWindow //наследуем функции и поля класса QMainWindow
{
    Q_OBJECT

public: //публичные методы
    explicit MainWindow(QWidget *parent = 0);//конструктор класса,  * - ссылка на адрес памяти
    ~MainWindow(); //деструктор класса (чтобы очищать память)

    enum class DrawingMode{ //всё дальше используется для объявления состояния программы, режимы, в понимании программы - это цифра. А мы сделали буквами, чтобы мы поняли. enum - нумиратор  
        ImageNotLoaded,
        ReadyForLinking, //готов для привязки
        Set1Point,
        Set2Point,
        SetRealCoord, //задать координаты
        ReadyForDigitizing //готов для оцифровки
    };

public slots: //слоты - это вещи, которые нужны для взаимодействия между моим классом и программой

private slots:
    void on_actionclose_triggered();

    void on_openimage_triggered();

    void on_zoomin_triggered();

    void on_zoomout_triggered();

    void on_left_triggered();

    void on_actionHomeView_triggered();

    void on_right_triggered();

    void on_actionlink_triggered();

    void on_up_triggered();

    void on_down_triggered();

    void showTable(); //чтобы показать табличку после привязки

    void showStatusMessage(QString);

    void on_pushButton_clicked();

    void on_actionsave_triggered();

    void on_actionopenGrid_triggered();

private:
    Ui::MainWindow *ui; //объект класса MainWindow, находящийся там же, потому что нам нужен только один объект из класса

};

class MyCanvas: public QLabel //MYcanvas занимает не всё окно, поэтому нам класс QLabel, чтобы рисовать только в части окна 
{
    Q_OBJECT

public:
    explicit MyCanvas(QWidget *parent){}
    ~MyCanvas(){}

    //рисования: две точки, линия
    enum class DrawingMode{
        ImageNotLoaded,
        ReadyForLinking,
        Set1Point,
        Set2Point,
        SetRealCoord,
        ReadyForDigitizing,
        DigitizingPolyLine,

    };

    MyScaler sc; //два наших класса и класс с картинкой
    Grid grid;
    QImage im;
    double ScaleFactor = 1.2; //масштабный коэф
    double ShiftFactor = 0.05; //коэф сдвига, чтобы картинку двигать
    DrawingMode mode = DrawingMode::ImageNotLoaded; //объявляем режим для рисования

    MyPolyline* polyline(){return &p1;} //создали свой класс, * - указатель на память, возвращаем адрес памяти объекта, & - берем адрес для памяти из объекта

signals:
    void signalShowTable();
    void signalShowStatusMessage(QString mes);

public slots:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);

protected slots: //защищенные слоты, форма доступа
    void resizeEvent(QResizeEvent * event);

private:
    QPoint mousePos=QPoint(0,0);
    MyPolyline p1;
};

#endif // MAINWINDOW_H
