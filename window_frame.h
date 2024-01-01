#ifndef __WINDOW_FRAME_H
#define __WINDOW_FRAME_H

#include "ui_popup.h"
#include <random>

typedef std::uniform_int_distribution<std::mt19937::result_type> uniform_dist;
typedef std::mt19937 rngen;

class WindowFrame : public QMainWindow {
    private:
        Ui::MainWindow ui;
        rngen &rng;
        uniform_dist &image_dist;
        uniform_dist &width_dist;
        uniform_dist &height_dist;
        void grab_click();
    public:
        WindowFrame(rngen &, uniform_dist &, uniform_dist &, uniform_dist &);
        QPushButton &get_button();
};

#endif // __WINDOW_MANAGER_H
