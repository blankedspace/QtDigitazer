#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug> //дебаги нужны только внутри программы, для отладки
#include <QString>
#include <QCoreApplication>
MainWindow::MainWindow(QWidget *parent) : //конструктор 
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); //указываем на объекты, которые вызывают функцию
    this->setMouseTracking(true);
    ui->canvas->sc.setScreenRect(QRectF(10,20,800,800));
    ui->canvas->sc.setFileSRect(QRectF(50,60,900,900)); //экранные, файловые
    ui->tableWidget->hide();
    ui->pushButton->hide();

    ui->canvas->mode = MyCanvas::DrawingMode::ImageNotLoaded;

    connect(ui->canvas,&MyCanvas::signalShowTable,this,&MainWindow::showTable); //соединить канвас и главное окно, :: - ссылка
    connect(ui->canvas,&MyCanvas::signalShowStatusMessage,this,&MainWindow::showStatusMessage);
}

MainWindow::~MainWindow() //деструктор
{
    delete ui;
}

void MyCanvas::paintEvent(QPaintEvent *event) //рисуем линию и цвета на гриде
{
    QPainter p(this); //инструмент рисования. мы передаем ему пространство для рисования MyCanvas
    QPen pen;
    pen.setColor(QColor(50,100,0));
    pen.setStyle(Qt::SolidLine);

    //QPointF pt1 = sc.file2Screen(sc.getFirstFPoint());

    p.drawImage(sc.screenRectF(),im, sc.fileSRectF()); //передаем два прямоугольника, картинку
    //ставим точки
    //QPen pen;
    pen.setColor(QColor(50,0,0));
    pen.setStyle(Qt::SolidLine);

    //qDebug() << grid.xSize/sc.fileSRectF().width(); //
    pen.setWidth(1000*(grid.xSize/(sc.fileSRectF().width())));
    p.setPen(pen);
    //чтение грида и цвета высот
    if(grid.values.size() != 0)
    {
        for (int i = 0; i < grid.xSize; ++i) { //i - столбики, j - строчки, grid.xSize - это максимальное значение X
            for (int j = 0; j < grid.ySize; ++j) {
                QPointF point(grid.xSize*10 - i*10,j*10); //умножаем на 10, чтобы разнести точки больше друг от друга
                QPointF pt1 = sc.file2Screen(point); //переводим координаты из файловых в экранные, чтобы они зависели от shiftfactor и scalefactor
                float data =  (grid.values[i+j*grid.xSize]/grid.maxValue); //значение грида в точки i j нормированная (от 0 до 1)
                pen.setColor(QColor(data*222,data*222,data*222)); //RGB, суммарно 255

                p.setPen(pen); //устанавливаем ручку
                p.drawPoint(pt1); //рисуем точку

            }
        }
    }

    pen.setWidth(5);
    p.setPen(pen);

    //ставим две точки
    if(mode == DrawingMode::Set2Point || mode == DrawingMode::SetRealCoord){ // || - логическое или
    QPointF pt1 = sc.file2Screen(sc.getFirstFPoint());
    p.drawEllipse(pt1,10,10); //первая точка
    p.drawLine(pt1.x()-5,pt1.y(),pt1.x()+5,pt1.y()); //пересеченные линии
    p.drawLine(pt1.x(),pt1.y()-5,pt1.x(),pt1.y()+5);
    p.drawText(pt1.x()-15,pt1.y()+15,"1");
    }

    if(mode == DrawingMode::SetRealCoord){
    QPointF pt2 = sc.file2Screen(sc.getSecondFPoint());
    p.drawEllipse(pt2,10,10); //вторая точка
    p.drawLine(pt2.x()-5,pt2.y(),pt2.x()+5,pt2.y());
    p.drawLine(pt2.x(),pt2.y()-5,pt2.x(),pt2.y()+5);
    p.drawText(pt2.x()+5,pt2.y()-5,"2");
    }
    //линия между точками
    else if(mode == DrawingMode::DigitizingPolyLine){
        pen.setColor(QColor(255,15,0));
        pen.setStyle(Qt::DashLine);
        pen.setWidth(1);
        p.setPen(pen);
        for(int i=1; i<p1.size(); i++){ //возвращаем линию между двумя точками
            QPointF pt1 = sc.file2Screen(p1.getPoint(i-1));
            QPointF pt2 = sc.file2Screen(p1.getPoint(i));
            p.drawLine(pt1,pt2);
        }
        //рисуем сами точки
        pen.setColor(QColor(128,10,0));
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(1);
        p.setPen(pen);
        for(int i=0; i<p1.size(); i++){
            QPointF pt = sc.file2Screen(p1.getPoint(i));
            const int w = 8;
            const int h = 8;
            p.drawRect(int(pt.x()-w/2),int(pt.y()-h/2),w,h);
    }
}}

void MyCanvas::mouseMoveEvent(QMouseEvent *event)
{
    //показывает файловые и реальные координаты, % - это тип данных
    QString mes = tr("x=%1; y=%2; ").arg(event->x()).arg(event->y()); //создать строку со значениями мышки
    QPointF filePoint = sc.screen2File(event->pos()); //перевод значения мышки в файловые координаты
    mes+=tr("fx=%1; fy=%2; ").arg(filePoint.x()).arg(filePoint.y());

    QPointF realPoint = sc.file2Real(filePoint);
    mes+=tr("rx=%1; ry=%2").arg(realPoint.x()).arg(realPoint.y());
    emit signalShowStatusMessage(mes); //emit - вызвать сигнал
}

void MyCanvas::mousePressEvent(QMouseEvent *event)
{
    //ставим две точки, рисуем, переводим из экранных координат в файловые
    if(mode == DrawingMode::Set1Point){
        QPoint screenPoint = event->pos(); //взять значения мышки
        QPointF filePoint = sc.screen2File(screenPoint); 
        sc.setFirstFPoint(filePoint);
        mode = DrawingMode::Set2Point;
        repaint();
    }
    else if (mode == DrawingMode::Set2Point){
        QPoint screenPoint = event->pos();
        QPointF filePoint = sc.screen2File(screenPoint);
        sc.setSecondFPoint(filePoint);
        mode = DrawingMode::SetRealCoord;

    emit signalShowTable(); //конвертация параметров в строку и добавление кода в начале
    }
    else if(mode==DrawingMode::DigitizingPolyLine){
        if(event->button() == Qt::LeftButton){
        QPoint screenPoint = event->pos();
        QPointF filePoint = sc.screen2File(screenPoint);
        p1.addPoint(filePoint);
        QPointF rp = sc.file2Real(filePoint);
        qDebug() << rp;
    }
        else if(event->button() == Qt::RightButton){
            if(p1.size()>0)p1.removeLastPoint();
        }

        repaint();
    }
}

void MyCanvas::resizeEvent(QResizeEvent *event)
{
    sc.setScreenRect(QRectF(0,0,width(),height())); //когда мы увеличиваем или уменьшаем окно, программа перерисовывает объект
}

void MainWindow::on_actionclose_triggered()
{
    close();
}

void MainWindow::on_openimage_triggered() //открываем изображение
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть изображение"), "D:\\Student\\_Maksimova");
    if(fileName.isEmpty())return;

    bool ok = ui->canvas->im.load(fileName); //возвращаем ok, если функция что-то загрузила
    if(!ok) {
        QMessageBox::warning(this, tr("Сообщение"), tr("Не могу загрузить изображение %l").arg(fileName));
        return;
    }

    ui->canvas->mode = MyCanvas::DrawingMode::ReadyForLinking;

    on_actionHomeView_triggered();

    ui->canvas->sc.setFileSRect(QRectF(ui->canvas->im.rect())); //устанавливаем размеры файлового прям. (изображения)
    ui->canvas->sc.setScreenRect(QRectF(0,0,width(),height())); //экранного прям.
    repaint();
}

void MainWindow::on_zoomin_triggered()
{
    QRectF r=ui->canvas->sc.fileSRectF();
    double xc = (r.left()+r.right())/2; //файловые координаты
    double yc = (r.top()+r.bottom())/2;

    double w = r.width()/ui->canvas->ScaleFactor;
    double h = r.height()/ui->canvas->ScaleFactor;

    ui->canvas->sc.setFileSRect(QRectF(xc-w/2,yc-h/2,w,h));

    repaint();
}

void MainWindow::on_zoomout_triggered()
{
    QRectF r=ui->canvas->sc.fileSRectF();
    double xc = (r.left()+r.right())/2; //задаём координаты центра
    double yc = (r.top()+r.bottom())/2;
    //уменьшаем файловый прямоугольник, чтобы приблизить
    double w = r.width()*ui->canvas->ScaleFactor;
    double h = r.height()*ui->canvas->ScaleFactor;

    ui->canvas->sc.setFileSRect(QRectF(xc-w/2,yc-h/2,w,h)); //отрисовываем прямоугольник с левого верхнего угла

    repaint();
}

void MainWindow::on_left_triggered()
{
    QRectF r=ui->canvas->sc.fileSRectF();
    double shift = ui->canvas->ShiftFactor *ui->canvas->sc.screenRect().width(); //умножаем, чтобы двигался на одинаковую длину
    r.setLeft(r.left() + shift); //установили левый край
    r.setRight(r.right() + shift); //установили правый край
    ui->canvas->sc.setFileSRect(r); //меняем файловые координаты
    repaint();
}

void MainWindow::on_actionHomeView_triggered()
{
    ui->canvas->sc.setFileSRect(QRectF(ui->canvas->im.rect()));
    if (ui->canvas->grid.xSize !=0){
        ui->canvas->sc.setFileSRect(QRectF(0,0,ui->canvas->grid.xSize*10, ui->canvas->grid.ySize*10));
    }


    ui->canvas->sc.setScreenRect(QRectF(0,0, width(), height()));
    repaint();
}

void MainWindow::on_right_triggered()
{
    QRectF r=ui->canvas->sc.fileSRectF();
    double shift = ui->canvas->ShiftFactor*ui->canvas->sc.screenRect().width();
    r.setLeft(r.left() - shift);
    r.setRight(r.right() - shift);
    ui->canvas->sc.setFileSRect(r);
    repaint();
}

void MainWindow::on_actionlink_triggered()
{
    QString mes = tr("Укажите на экране 2 точки, затем задайте их координаты");
    QMessageBox::warning(this, tr("Сообщение"), mes);
    ui->canvas->mode = MyCanvas::DrawingMode::Set1Point;

}

void MainWindow::on_up_triggered()
{
    QRectF r=ui->canvas->sc.fileSRectF();
    double shift = ui->canvas->ShiftFactor*ui->canvas->sc.screenRect().height();
    r.setTop(r.top() + shift);
    r.setBottom(r.bottom() + shift);
    ui->canvas->sc.setFileSRect(r);
    repaint();
}

void MainWindow::on_down_triggered()
{
    QRectF r=ui->canvas->sc.fileSRectF();
    double shift = ui->canvas->ShiftFactor*ui->canvas->sc.screenRect().height();
    r.setTop(r.top() - shift);
    r.setBottom(r.bottom() - shift);
    ui->canvas->sc.setFileSRect(r);
    repaint();
}

void MainWindow::showTable()
{
    ui->tableWidget->show();
    ui->pushButton->show();
}

void MainWindow::showStatusMessage(QString mes)
{
    ui->statusBar->showMessage(mes);
}

void MainWindow::on_pushButton_clicked() //привязать
{
    //QString mes = tr("Не корректно задано число в ячейке: строка %1, колонка %2.");
    bool ok;


    double xr1 = ui->tableWidget->item(0,0)->text().toDouble(&ok);
    double xr2 = ui->tableWidget->item(1,0)->text().toDouble(&ok);
    double yr1 = ui->tableWidget->item(0,1)->text().toDouble(&ok);
    double yr2 = ui->tableWidget->item(1,1)->text().toDouble(&ok);

    ui->canvas->sc.setFirstRPoint(QPointF(xr1,yr1));
    ui->canvas->sc.setSecondRPoint(QPointF(xr2,yr2));

    ui->canvas->mode = MyCanvas::DrawingMode::DigitizingPolyLine; //включили прорисовку линии
    //отключили справа окошко
    ui->tableWidget->hide();
    ui->pushButton->hide();
}

void MainWindow::on_actionsave_triggered()
{

     QString filename = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "M:\\trueDigitazer\\test", "CSV Files (*.csv");
     QFile file(filename);
     file.open(QIODevice::WriteOnly | QIODevice::Text);
     int size = ui->canvas->polyline()->size();
     QTextStream stream(&file); //значок нужен, чтобы программа передавала не в копию, а в сам файл
     for (int i = 0; i<size; i++){
        QPointF tochka = ui->canvas->polyline()->getPoint(i);
        tochka = ui->canvas->sc.file2Real(tochka);
        stream << tochka.x() << ";" << tochka.y() << "\n";
     }
     file.close();
}


void MainWindow::on_actionopenGrid_triggered() //открываем грид
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть грид"), "M:\\trueDigitazer\\test"); //заходим в папку
    if(fileName.isEmpty())return;
    Grid tempGrid; //задаем
    bool StartReadingData = false;
    QFile inputFile(fileName); //открыли файл
    if (inputFile.open(QIODevice::ReadOnly)) //считываем файл
    {
       QTextStream in(&inputFile);
       //считываем шапку файла
       while (!in.atEnd())
       {
          QString line = in.readLine();
          if(line.contains("FSNROW"))
          {
              QStringList list = line.split(" ");
              for(auto word: list) //проходим по всем словам
              {
                  bool ok;
                  int number = word.toInt(&ok);
                  if(ok)
                  {
                    //qDebug() << number;

                        if(tempGrid.xSize != 0)
                        {
                           tempGrid.ySize = number;
                        }
                        if(tempGrid.xSize == 0)
                        {
                           tempGrid.xSize = number;
                        }
                  }
              }

          }
          //считываем цифры для построения грида

          if(StartReadingData)
          {
              QStringList list = line.split(" "); //разбиваем на слова. проверяем, что слово - это цифра
              for(auto word: list)
              {
                  bool ok;
                  float number = word.toFloat(&ok);
                  if(ok)
                  {
                    if(number > tempGrid.maxValue) //поиск максимального числа
                    {
                        tempGrid.maxValue = number;
                    }
                     tempGrid.values.push_back(number);
                  }
              }
          }
          if(line.contains("->Default"))
          {
                  StartReadingData = true;
            }

       }
       //записываем данные в поток и выгружаем в виде "пикселей"
       qDebug() << tempGrid.values.size();
       qDebug() << tempGrid.xSize * tempGrid.ySize;
       ui->canvas->grid = tempGrid;
       ui->canvas->sc.setScreenRect(QRectF(0,0,width(),height()));
       ui->canvas->sc.setFileSRect(ui->canvas->sc.screenRect());
       on_actionHomeView_triggered();
       inputFile.close();
    }

    repaint(); //перерисовка изображения
}

