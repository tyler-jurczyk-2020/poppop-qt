#include "video_frame.h"
#include <KX11Extras>

VideoFrame::VideoFrame() {
    ui.setupUi(this);
    QRect workspace = KX11Extras::workArea();
    setGeometry(16, 16, workspace.width() - 32, workspace.height() - 32);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
    QPixmap pixmap = QPixmap("/home/tysonthebison/.config/systemd/poppop-qt/videos/thumbnails/f_1.jpg").scaledToWidth(workspace.width() - 32, Qt::SmoothTransformation);
    ui.label->setPixmap(pixmap);
    float upshift = -1.0f*(pixmap.height() - workspace.height())/2;
    ui.label->setGeometry(0, upshift, pixmap.width(), pixmap.height());
    ui.label->lower(); // Ensures this is on the bottom of the widget stack
    // Set blurring
    blur.setBlurRadius(100);
    ui.label->setGraphicsEffect(&blur);

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
