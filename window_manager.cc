#include "window_manager.h"
#include <memory>
#include <QTimer>

void WindowManager::spawn_window() {
    frames.push_back(std::make_unique<WindowFrame>(rng, dist));
}

WindowManager::WindowManager() {
    
    // Setup random number generator to be used for all windows
    std::random_device dev;
    rng = std::mt19937(dev());
    dist = std::uniform_int_distribution<std::mt19937::result_type>(1,10);    
    //Spawn the first window
    frames.push_back(std::make_unique<WindowFrame>(rng, dist));
    connect(&timer, &QTimer::timeout, this, &WindowManager::spawn_window);
    timer.start(4000);
}
