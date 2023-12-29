#include "window_manager.h"
#include <memory>
#include <QTimer>
#include <qnamespace.h>

void WindowManager::spawn_window() {
    auto frame_ptr = std::make_unique<WindowFrame>(rng, dist);
    connect(&frame_ptr->get_button(), &QPushButton::clicked, this, &WindowManager::handle_interaction);
    frames.push_back(std::move(frame_ptr));
    info.setText("New window spawned!");
    info.show();
}

void WindowManager::handle_interaction() {
    qDebug() << "Handling in manager!" << Qt::endl;
    emit info.accept(); 
}

WindowManager::WindowManager() : info(QMessageBox::Information, "mytitle", "mytext", QMessageBox::NoButton, nullptr, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus) {
    
    // Setup random number generator to be used for all windows
    std::random_device dev;
    rng = std::mt19937(dev());
    dist = std::uniform_int_distribution<std::mt19937::result_type>(1,10);    
    //Spawn the first window
    info.setStandardButtons(QMessageBox::NoButton);
    info.setModal(false);
    spawn_window();

    
    
    // Setup timer
    connect(&timer, &QTimer::timeout, this, &WindowManager::spawn_window);
    timer.start(8000);
}
