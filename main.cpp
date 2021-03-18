#include "multifunctool.h"
#include <QtWidgets/QApplication>

#include "RParser.h"

int main(int argc, char *argv[])
{
    RParser::GetConfig();

    QApplication a(argc, argv);
    multifunctool w;
    w.show();
    return a.exec();
}
