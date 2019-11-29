#include <QApplication>

#include "_setup.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    _SetUp setp;
    //setup.show();

    return a.exec();
}
