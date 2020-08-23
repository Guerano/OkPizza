#include "view/mainwindow.hpp"

#include <QApplication>
#include <QDebug>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("Fusion");
    MainWindow w;
    w.show();
    return a.exec();
}
