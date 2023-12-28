#ifndef __WINDOW_MANAGER_H
#define __WINDOW_MANAGER_H

#include "window_frame.h"
#include <vector>

class WindowManager {
    private:
        std::vector<std::unique_ptr<WindowFrame>> frames;
        std::mt19937 rng;
        std::uniform_int_distribution<std::mt19937::result_type> dist;    
    public:
        WindowManager();
};

#endif
