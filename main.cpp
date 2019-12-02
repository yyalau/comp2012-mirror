#include <QApplication>

#include "_setup.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    _SetUp setup;

    return a.exec();
}
