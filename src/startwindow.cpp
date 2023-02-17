#include "startwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include "datamanager.h"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    UI(new Ui::MainWindow)
{
    UI->setupUi(this);
    this->setMouseTracking(true);
    UI->canvas->sc.setScreenRect(QRectF(10,20,800,800));
    UI->canvas->sc.setFileSRect(QRectF(50,60,900,900));
    UI->tableWidget->hide();
    UI->pushButton->hide();

    //UI->mode = DrawableWin\dow::DrawingMode::ImageNotLoaded;

    connect(UI->canvas,&DrawableWindow::signalShowTable,this,&StartWindow::showTable);
    connect(UI->canvas,&DrawableWindow::signalShowStatusMessage,this,&StartWindow::showStatusMessage);

}

StartWindow::~StartWindow()
{
}

void StartWindow::on_actionclose_triggered()
{
    close();
}

void StartWindow::on_openimage_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть изображение"), "");
    if(fileName.isEmpty())return;

    DataManager::LoadImage(fileName);
    /*
    bool ok = UI->canvas->im.load(fileName);
    if(!ok) {
        QMessageBox::warning(this, tr("Сообщение"), tr("Не могу загрузить изображение %l").arg(fileName));
        return;
    }*/

    UI->canvas->mode = DrawableWindow::DrawingMode::ReadyForLinking;

    on_actionHomeView_triggered();

    //UI->canvas->sc.setFileSRect(QRectF(UI->canvas->im.rect()));
    //UI->canvas->sc.setScreenRect(QRectF(0,0,width(),height()));
    repaint();
}

void StartWindow::on_zoomin_triggered()
{
    QRectF r=UI->canvas->sc.fileSRectF();
    double xc = (r.left()+r.right())/2;
    double yc = (r.top()+r.bottom())/2;

    double w = r.width()/UI->canvas->ScaleFactor;
    double h = r.height()/UI->canvas->ScaleFactor;

    UI->canvas->sc.setFileSRect(QRectF(xc-w/2,yc-h/2,w,h));

    repaint();
}

void StartWindow::on_zoomout_triggered()
{
    QRectF r=UI->canvas->sc.fileSRectF();
    double xc = (r.left()+r.right())/2;
    double yc = (r.top()+r.bottom())/2;

    double w = r.width()*UI->canvas->ScaleFactor;
    double h = r.height()*UI->canvas->ScaleFactor;

    UI->canvas->sc.setFileSRect(QRectF(xc-w/2,yc-h/2,w,h));

    repaint();
}

void StartWindow::on_left_triggered()
{
    QRectF r=UI->canvas->sc.fileSRectF();
    double shift = UI->canvas->ShiftFactor *UI->canvas->sc.screenRect().width();
    r.setLeft(r.left() + shift);
    r.setRight(r.right() + shift);
    UI->canvas->sc.setFileSRect(r);
    repaint();
}

void StartWindow::on_actionHomeView_triggered()
{
   /* UI->canvas->sc.setFileSRect(QRectF(UI->canvas->im.rect()));
    if (UI->canvas->grid.xSize !=0){
        UI->canvas->sc.setFileSRect(QRectF(0,0,UI->canvas->grid.xSize*10, UI->canvas->grid.ySize*10));
    }
    */

    UI->canvas->sc.setScreenRect(QRectF(0,0, width(), height()));
    repaint();
}

void StartWindow::on_right_triggered()
{
    QRectF r=UI->canvas->sc.fileSRectF();
    double shift = UI->canvas->ShiftFactor*UI->canvas->sc.screenRect().width();
    r.setLeft(r.left() - shift);
    r.setRight(r.right() - shift);
    UI->canvas->sc.setFileSRect(r);
    repaint();
}

void StartWindow::on_actionlink_triggered()
{
    QString mes = tr("Укажите на экране 2 точки, затем задайте их координаты");
    QMessageBox::warning(this, tr("Сообщение"), mes);
    UI->canvas->mode = DrawableWindow::DrawingMode::Set1Point;

}

void StartWindow::on_up_triggered()
{
    QRectF r=UI->canvas->sc.fileSRectF();
    double shift = UI->canvas->ShiftFactor*UI->canvas->sc.screenRect().height();
    r.setTop(r.top() + shift);
    r.setBottom(r.bottom() + shift);
    UI->canvas->sc.setFileSRect(r);
    repaint();
}

void StartWindow::on_down_triggered()
{
    QRectF r=UI->canvas->sc.fileSRectF();
    double shift = UI->canvas->ShiftFactor*UI->canvas->sc.screenRect().height();
    r.setTop(r.top() - shift);
    r.setBottom(r.bottom() - shift);
    UI->canvas->sc.setFileSRect(r);
    repaint();
}

void StartWindow::showTable()
{
    UI->tableWidget->show();
    UI->pushButton->show();
}

void StartWindow::showStatusMessage(QString mes)
{
    UI->statusBar->showMessage(mes);
}

void StartWindow::on_pushButton_clicked()
{
    //QString mes = tr("Не корректно задано число в ячейке: строка %1, колонка %2.");
    bool ok;


    double xr1 = UI->tableWidget->item(0,0)->text().toDouble(&ok);
    double xr2 = UI->tableWidget->item(1,0)->text().toDouble(&ok);
    double yr1 = UI->tableWidget->item(0,1)->text().toDouble(&ok);
    double yr2 = UI->tableWidget->item(1,1)->text().toDouble(&ok);

    UI->canvas->sc.setFirstRPoint(QPointF(xr1,yr1));
    UI->canvas->sc.setSecondRPoint(QPointF(xr2,yr2));

    UI->canvas->mode = DrawableWindow::DrawingMode::DigitizingPolyLine; //включили прорисовку линии
    //отключили справа окошко
    UI->tableWidget->hide();
    UI->pushButton->hide();
}

void StartWindow::on_actionsave_triggered()
{

     QString filename = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "M:\\trueDigitazer\\test", "CSV Files (*.csv");
     QFile file(filename);
     file.open(QIODevice::WriteOnly | QIODevice::Text);
     int size = UI->canvas->polyline()->size();
     QTextStream stream(&file); //значок нужен, чтобы программа передавала не в копию, а в сам файл
     for (int i = 0; i<size; i++){
        QPointF tochka = UI->canvas->polyline()->getPoint(i);
        tochka = UI->canvas->sc.file2Real(tochka);
        stream << tochka.x() << ";" << tochka.y() << "\n";
     }
     file.close();
}

void StartWindow::on_actionopenGrid_triggered() //открываем грид
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть грид"), "M:\\trueDigitazer\\test"); //заходим в папку
    if(fileName.isEmpty())return;
    DataManager::LoadGrid(fileName);

   //записываем данные в поток и выгружаем в виде "пикселей"

   UI->canvas->sc.setScreenRect(QRectF(0,0,width(),height()));
   UI->canvas->sc.setFileSRect(UI->canvas->sc.screenRect());
   on_actionHomeView_triggered();

    repaint(); //перерисовка изображения
}

