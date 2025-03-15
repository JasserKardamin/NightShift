#include "nightshift.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NightShift w;
    w.show();
    return a.exec();
}
