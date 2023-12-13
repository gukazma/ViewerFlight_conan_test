#include <QApplication>
#include "MainWindow.h"
#include <osgEarth/Common>
int main(int argc, char** argv)
{
    osgEarth::initialize();
    QApplication app(argc, argv);

    MainWindow mainwinndow;

    mainwinndow.show();

    return app.exec();
}
