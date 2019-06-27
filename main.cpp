#include "mainwindow.h"
#include <QApplication>
#include<QSplashScreen>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QPixmap pixmap(":/Resource/start.PNG");
    QSplashScreen splash(pixmap);
    splash.show();
    for(long index = 0; index < 1000000000; index++);//显示延时
    splash.finish(&w);
    w.show();
    w.setWindowIcon(QIcon(":/Resource/tongji.ico"));
    return a.exec();
}
