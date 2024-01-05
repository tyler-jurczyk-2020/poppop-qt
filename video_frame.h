#ifndef __VIDEO_FRAME_H
#define __VIDEO_FRAME_H

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMainWindow>
#include "ui_video.h"

class VideoFrame : public QMainWindow {
    public:
        Ui::PoppopVideo ui;
        QMediaPlayer player;
        VideoFrame();
};

#endif
