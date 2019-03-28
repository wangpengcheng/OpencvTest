#include "mainwindow.h"
#include <iostream>
#include <QCoreApplication>
#include <QApplication>
#include "mystitcher.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //std::cout<<"hello word!"<<std::endl;
   // change_image();
    //MyStitcher stitcher_test;
    //stitcher_test.StitchImages();
    MainWindow w;
    w.show();
    return a.exec();
}
