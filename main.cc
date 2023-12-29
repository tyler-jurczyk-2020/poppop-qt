#include <QApplication>
#include <random>
#include "window_manager.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    WindowManager wm; 
    return app.exec();
}

