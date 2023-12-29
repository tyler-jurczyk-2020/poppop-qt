#ifndef __WINDOW_FRAME_H
#define __WINDOW_FRAME_H

#include "ui_popup.h"
#include <qmainwindow.h>
#include <random>

class WindowFrame : public QMainWindow {
    private:
        Ui::MainWindow ui;
        void grab_click();
    public:
        WindowFrame(std::mt19937 &, std::uniform_int_distribution<std::mt19937::result_type>);
        QPushButton &get_button();
};

#endif // __WINDOW_MANAGER_H
