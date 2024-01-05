#include "video_frame.h"
#include <QMediaPlayer>

VideoFrame::VideoFrame(){
    ui.setupUi(this);
    setGeometry(0, 0, 1550, 800);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);

    player.setVideoOutput(ui.widget);
    playlist.addMedia(QUrl::fromLocalFile("/home/tysonthebison/.config/systemd/poppop-qt/videos/f_1.mp4"));
    player.setPlaylist(&playlist);
    playlist.setCurrentIndex(1);
}

void VideoFrame::play() {
    show();
    player.play();
}
