#include "window_manager.h"
#include "window_frame.h"
#include <KX11Extras>
#include <memory>

void WindowManager::spawn_window() {
    connect(KX11Extras::self(), &KX11Extras::windowAdded, this, &WindowManager::get_window_id);
    last_created_window = std::make_unique<WindowFrame>(rng, image_dist, width_dist, height_dist);
    }

void WindowManager::get_window_id(WId id) {
    // May be bad practice to call get() on unique_ptr
    last_created_window->set_window_id(id);
    connect(last_created_window.get(), &WindowFrame::received_button_push, this, &WindowManager::handle_interaction);
    frames.insert({id, std::move(last_created_window)});
    info.setText("New window spawned!");
//    info.show();
    disconnect(KX11Extras::self(), &KX11Extras::windowAdded, this, &WindowManager::get_window_id);
}

void WindowManager::handle_interaction(WId id) {
    Action action = static_cast<Action>(selector(rng));
    switch (action) {
        /*
        case OPEN_GIF:
            frames.erase(id);
            vframe.set_gifs({1, 2});
            vframe.play();
            break;
        */
        case OPEN_VIDEO:
            frames.erase(id);
            vframe.set_video(1);
            vframe.play();
            break;
        /*
        case CLOSE_WINDOW:
            frames.erase(id);
            break; 
        case OPEN_WINDOW:
            spawn_window();
            break;
        */
        default:
            break;
    }
    info.hide();
}

// NEED TO UPDATE RANGE OF NUMBER GENERATOR
WindowManager::WindowManager() : 
rng(dev()), image_dist(uniform_dist(1,10)),
width_dist(uniform_dist(0,1550)),
height_dist(uniform_dist(0,800)),
selector(uniform_dist(0,3)),
info(QMessageBox::Information, "MainWindow", "mytext", QMessageBox::NoButton, nullptr, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus) {
    
    // Modify popup
    info.setStandardButtons(QMessageBox::NoButton);
    info.setModal(false);

    //Spawn the first window
    spawn_window();
    
    // Setup timer
    connect(&timer, &QTimer::timeout, this, &WindowManager::spawn_window);
    timer.start(60000);
}
