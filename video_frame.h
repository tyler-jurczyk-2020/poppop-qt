#ifndef __VIDEO_FRAME_H
#define __VIDEO_FRAME_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QMainWindow>
#include <QGraphicsBlurEffect>
#include <QProcess>
#include <QTimer>
#include <vector>
#include "ui_video.h"

class VideoFrame : public QMainWindow {
    private:
        Ui::PoppopVideo ui;
        QMediaPlayer player;
        QMediaPlaylist playlist;
        QGraphicsBlurEffect blur;
        QGraphicsBlurEffect blur2;
        QTimer adjuster;
        bool is_label_two_next;
        std::list<QPixmap> thumbnails;
        QProcess volume_setter;

        void handleMediaChange();
        void handleAddedWindow(WId);

    public:
        VideoFrame();
        void play();
        void adjust_volume();
        void set_video(int);
};

#endif
