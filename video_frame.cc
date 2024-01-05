#include "video_frame.h"

VideoFrame::VideoFrame() {
    ui.setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
    setGeometry(0, 0, 1550, 800);
}
