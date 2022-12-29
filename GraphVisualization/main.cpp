#include "paintwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaintWidget p;
    p.setWindowTitle("图的关键路径");
    p.show();

    return a.exec();
}
