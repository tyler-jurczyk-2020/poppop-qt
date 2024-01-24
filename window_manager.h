#ifndef __WINDOW_MANAGER_H
#define __WINDOW_MANAGER_H

#include "window_frame.h"
#include "video_frame.h"
#include <QTimer>
#include <QMessageBox>
#include <memory>
#include <unordered_map>

enum Action {
    CLOSE_WINDOW,
    OPEN_GIF,
    OPEN_VIDEO,
};

class WindowManager : public QObject {
    private:
        std::random_device dev;
        rngen rng;
        uniform_dist image_dist;    
        uniform_dist width_dist;
        uniform_dist height_dist;
        uniform_dist selector;
        std::unique_ptr<WindowFrame> last_created_window;
        std::unordered_map<WId, std::unique_ptr<WindowFrame>> frames;
        VideoFrame vframe;
        QMessageBox info;
        QTimer timer;
        void spawn_window();
        void handle_interaction(WId);
        void get_window_id(WId);
    public:
        WindowManager();
};

#endif
