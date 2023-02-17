#include "startwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(Buttons);

    StartWindow w;
    w.show();

    return a.exec();
}
