#include <QtGui/QApplication>
#include "./babelClient/MainWindow.h"
#include <QFile>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile fileStyle("./babelStyle.css");

    if (fileStyle.open(QIODevice::ReadOnly))
    {
        a.setStyleSheet(fileStyle.readAll());
        fileStyle.close();
    }

    MainWindow w;
    w.show();

    return a.exec();
}
