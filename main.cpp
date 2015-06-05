#include "mainwindow.h"
#include <QApplication>
/*! Leah Briscoe PIC10C Spring 2015
 * Main calls the MainWindow
 */

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
