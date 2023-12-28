#include <QApplication>
#include <random>
#include "window_manager.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    WindowManager wm; 
    return app.exec();
}

