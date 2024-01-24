#ifndef __WINDOW_FRAME_H
#define __WINDOW_FRAME_H

#include "ui_popup.h"
#include <memory>
#include <random>

typedef std::uniform_int_distribution<std::mt19937::result_type> uniform_dist;
typedef std::mt19937 rngen;

class WindowFrame : public QMainWindow {
    Q_OBJECT
    private:
        Ui::MainWindow ui;
        WId wid;
        rngen &rng;
        uniform_dist &image_dist;
        uniform_dist &width_dist;
        uniform_dist &height_dist;
        void grab_click();
    public:
        WindowFrame(rngen &, uniform_dist &, uniform_dist &, uniform_dist &);
        void set_window_id(WId);
    signals:
        void received_button_push(WId);
};

#endif // __WINDOW_MANAGER_H
