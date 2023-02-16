#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(Buttons);//приложение Qt, объект класса
    QFile mfile(":/Assets/Buttons/left.png");
    if(!mfile.open(QFile::ReadOnly))
    {
        qDebug() << "could not open file";
    }
    qDebug() << "Loaded file";
    MainWindow w;
    w.show();

    return a.exec();
}
