#include <QApplication>

#include "_setup.h"

extern _SetUp* setup;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    _SetUp* setup= new _SetUp;
    setup->show();

    return a.exec();
}
