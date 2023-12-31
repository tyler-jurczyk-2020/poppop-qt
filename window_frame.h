#ifndef __WINDOW_FRAME_H
#define __WINDOW_FRAME_H

#include "ui_popup.h"
#include <qmainwindow.h>
#include <random>

class WindowFrame : public QMainWindow {
    private:
        Ui::MainWindow ui;
        void grab_click();
        std::mt19937 rng_w;
        std::mt19937 rng_h;
        std::uniform_int_distribution<std::mt19937::result_type> dist_w;
        std::uniform_int_distribution<std::mt19937::result_type> dist_h;
    public:
        WindowFrame(std::mt19937 &, std::uniform_int_distribution<std::mt19937::result_type>, std::random_device::result_type);
        QPushButton &get_button();
};

#endif // __WINDOW_MANAGER_H
