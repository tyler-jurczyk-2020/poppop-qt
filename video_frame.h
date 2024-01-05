#ifndef __VIDEO_FRAME_H
#define __VIDEO_FRAME_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QMainWindow>
#include <QGraphicsBlurEffect>
#include "ui_video.h"

class VideoFrame : public QMainWindow {
    private:
        Ui::PoppopVideo ui;
        QMediaPlayer player;
        QMediaPlaylist playlist;
        QGraphicsBlurEffect blur;
    public:
        VideoFrame();
        void handleMediaChange();
        void play();
};

#endif
