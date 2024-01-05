#include "video_frame.h"
#include <QMediaPlayer>
#include <KX11Extras>

VideoFrame::VideoFrame() : playQueued(false) {
    ui.setupUi(this);
    QRect workspace = KX11Extras::workArea();
    setGeometry(16, 16, workspace.width() - 32, workspace.height() - 32);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);

    player.setVideoOutput(ui.widget);
    playlist.addMedia(QUrl::fromLocalFile("/home/tysonthebison/.config/systemd/poppop-qt/videos/f_1.mp4"));
    player.setPlaylist(&playlist);

    connect(&player, &QMediaPlayer::mediaStatusChanged, this, &VideoFrame::handleMediaChange);
}

void VideoFrame::handleMediaChange() {
    if (player.mediaStatus() == QMediaPlayer::LoadedMedia) {
        QRect workspace = KX11Extras::workArea();
        QSize resolution = player.metaData("Resolution").value<QSize>();
        float scaled_width = resolution.width() * (static_cast<float>(workspace.height()-32)/resolution.height());
        qDebug() << scaled_width << Qt::endl;
        int horiz_center = (workspace.width() - 32 - scaled_width)/2;
        ui.widget->setGeometry(horiz_center, 0, scaled_width, workspace.height()-32);
        qDebug() << player.availableMetaData() << Qt::endl;
    }
}

void VideoFrame::play() {
    playlist.setCurrentIndex(1); // Prevents delay?
    show();
    player.play();
}
