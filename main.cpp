#include "multifunctool.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    multifunctool w;
    w.show();
    return a.exec();
}
