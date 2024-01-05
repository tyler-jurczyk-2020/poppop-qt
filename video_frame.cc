#include "video_frame.h"
#include <QTimer>
#include <KX11Extras>

VideoFrame::VideoFrame() {
    ui.setupUi(this);
    QRect workspace = KX11Extras::workArea();
    setGeometry(16, 16, workspace.width() - 32, workspace.height() - 32);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
    ui.label->lower(); // Ensures this is on the bottom of the widget stack
    // Set blurring
    blur.setBlurRadius(100);
    ui.label->setGraphicsEffect(&blur);

    player.setVideoOutput(ui.widget);
    // Loading media should NOT HAPPEN IN CONSTRUCTOR
    playlist.addMedia(QUrl::fromLocalFile("/home/tysonthebison/.config/systemd/poppop-qt/videos/f_1.mp4"));
    playlist.addMedia(QUrl::fromLocalFile("/home/tysonthebison/.config/systemd/poppop-qt/videos/f_2.mp4"));
    player.setPlaylist(&playlist);
    
    connect(&player, &QMediaPlayer::mediaStatusChanged, this, &VideoFrame::handleMediaChange);
}

void VideoFrame::handleAddedWindow(WId id) {
    KX11Extras::setOnAllDesktops(id, true);
    disconnect(KX11Extras::self(), &KX11Extras::windowAdded, this, &VideoFrame::handleAddedWindow);
}

void VideoFrame::handleMediaChange() {
    // Smooths out transition between clips
    if (player.mediaStatus() == QMediaPlayer::EndOfMedia) {
        ui.widget->hide();
        QTimer::singleShot(150, ui.widget, &QVideoWidget::show);
    }
    if (player.mediaStatus() == QMediaPlayer::BufferedMedia) {
        // Scale video correctly
        QRect workspace = KX11Extras::workArea();
        QSize resolution = player.metaData("Resolution").value<QSize>();
        float scaled_width = resolution.width() * (static_cast<float>(workspace.height()-32)/resolution.height());
        int horiz_center = (workspace.width() - 32 - scaled_width)/2;
        ui.widget->setGeometry(horiz_center, 0, scaled_width, workspace.height()-32);

        // Setup corresponding background picture
        QString filename = player.metaData("Title").value<QString>();
        QString target = filename.left(filename.length() - 4);
        QString path = QString("/home/tysonthebison/.config/systemd/poppop-qt/videos/thumbnails/%1.jpg").arg(target);
        qDebug() << target << Qt::endl;
        QPixmap pixmap = QPixmap(path).scaledToWidth(workspace.width() - 32, Qt::SmoothTransformation);
        ui.label->setPixmap(pixmap);
        float upshift = -1.0f*(pixmap.height() - workspace.height())/2;
        ui.label->setGeometry(0, upshift, pixmap.width(), pixmap.height());
        show();
    }
}

void VideoFrame::play() {
    connect(KX11Extras::self(), &KX11Extras::windowAdded, this, &VideoFrame::handleAddedWindow);
    playlist.setCurrentIndex(0);
    player.play();
}
