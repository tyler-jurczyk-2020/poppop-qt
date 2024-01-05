#include "window_manager.h"

void WindowManager::spawn_window() {
    auto frame_ptr = std::make_unique<WindowFrame>(rng, image_dist, width_dist, height_dist);
    connect(&frame_ptr->get_button(), &QPushButton::clicked, this, &WindowManager::handle_interaction);
    frames.push_back(std::move(frame_ptr));
    info.setText("New window spawned!");
    info.show();
}

void WindowManager::handle_interaction() {
    qDebug() << "Handling in manager!" << Qt::endl;
    vframe.play();
    info.hide();
}

// NEED TO UPDATE RANGE OF NUMBER GENERATOR
WindowManager::WindowManager() : 
rng(dev()), image_dist(uniform_dist(1,3)),
width_dist(uniform_dist(0,1550)),
height_dist(uniform_dist(0,800)),
info(QMessageBox::Information, "MainWindow", "mytext", QMessageBox::NoButton, nullptr, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus) {
    
    // Modify popup
    info.setStandardButtons(QMessageBox::NoButton);
    info.setModal(false);

    //Spawn the first window
    spawn_window();
    
    // Setup timer
    connect(&timer, &QTimer::timeout, this, &WindowManager::spawn_window);
    timer.start(8000);
}
