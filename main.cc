#include <QApplication>
#include <random>
#include "window_frame.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Setup random number generator to be used for all windows
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);    
    WindowFrame wm(rng, dist6);
    return app.exec();
}

