#include "mainwindow.h"
#include <QApplication>
#include "header.h"




int main(int argc, char *argv[])
{
    int i,j,k;
    QApplication a(argc, argv);
    MainWindow w;

    QTextStream cin(stdin,  QIODevice::ReadOnly);
    QTextStream cout(stdout,  QIODevice::WriteOnly);
    QTextStream cerr(stderr,  QIODevice::WriteOnly);

     w.setFixedSize(2500, 1500);

    w.show();
    return a.exec();
}
