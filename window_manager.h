#ifndef __WINDOW_MANAGER_H
#define __WINDOW_MANAGER_H

#include "window_frame.h"
#include <QTimer>
#include <QMessageBox>

class WindowManager : public QObject {
    private:
        std::random_device dev;
        rngen rng;
        uniform_dist image_dist;    
        uniform_dist width_dist;
        uniform_dist height_dist;
        std::vector<std::unique_ptr<WindowFrame>> frames;
        QMessageBox info;
        QTimer timer;
        void spawn_window();
        void handle_interaction();
    public:
        WindowManager();
};

#endif
