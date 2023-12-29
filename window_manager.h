#ifndef __WINDOW_MANAGER_H
#define __WINDOW_MANAGER_H

#include "window_frame.h"
#include <QTimer>
#include <vector>

class WindowManager : public QObject {
    private:
        std::vector<std::unique_ptr<WindowFrame>> frames;
        std::mt19937 rng;
        std::uniform_int_distribution<std::mt19937::result_type> dist;    
        QTimer timer;
        void spawn_window();
        void handle_interaction();
    public:
        WindowManager();
};

#endif
