#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QPen> //включаем классы Qt
#include <QBrush> 
#include <QColor>
#include <QPainter>
#include <QMouseEvent>
#include "dgzscaler.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>



namespace Ui {
class MainWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = 0);
    ~StartWindow();

    enum class DrawingMode{
        ImageNotLoaded,
        ReadyForLinking,
        Set1Point,
        Set2Point,
        SetRealCoord,
        ReadyForDigitizing
    };

public slots:

public slots:


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

    void showTable();

    void showStatusMessage(QString);

    void on_pushButton_clicked();

    void on_actionsave_triggered();

    void on_actionopenGrid_triggered();

private:
    Ui::MainWindow *UI;
};

#endif // STARTWINDOW_H
