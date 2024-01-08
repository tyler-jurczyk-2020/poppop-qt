#include "video_frame.h"
#include <QAudioDeviceInfo>
#include <KX11Extras>
#include <memory>

VideoFrame::VideoFrame() {
    ui.setupUi(this);
    QRect workspace = KX11Extras::workArea();
    setGeometry(16, 16, workspace.width() - 32, workspace.height() - 32);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
    ui.widget->raise();
    // Set blurring
    blur.setBlurRadius(100);
    blur2.setBlurRadius(100);
    ui.label->setGraphicsEffect(&blur);
    ui.label_2->setGraphicsEffect(&blur2);

    player.setVideoOutput(ui.widget);
    // Loading media should NOT HAPPEN IN CONSTRUCTOR
    playlist.addMedia(QUrl::fromLocalFile("/home/tysonthebison/.config/systemd/poppop-qt/videos/f_1.mp4"));
    playlist.addMedia(QUrl::fromLocalFile("/home/tysonthebison/.config/systemd/poppop-qt/videos/f_2.mp4"));
    // Setup labels
    thumbnails.push_back(QPixmap("/home/tysonthebison/.config/systemd/poppop-qt/videos/thumbnails/f_1.jpg"));
    thumbnails.push_back(QPixmap("/home/tysonthebison/.config/systemd/poppop-qt/videos/thumbnails/f_2.jpg"));
    player.setPlaylist(&playlist);
    //Enable Audio
    player.setVolume(100);

    // Setup double buffered backgrounds
    is_label_two_next = true;

    //connect(&adjuster, &QTimer::timeout, this, &VideoFrame::adjust_volume);

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
        adjuster.stop();
        QTimer::singleShot(250, ui.widget, &QVideoWidget::show);
    }
    if (player.mediaStatus() == QMediaPlayer::BufferedMedia) {
        // Scale video correctly
        QRect workspace = KX11Extras::workArea();
        QSize resolution = player.metaData("Resolution").value<QSize>();
        float scaled_width = resolution.width() * (static_cast<float>(workspace.height()-32)/resolution.height());
        int horiz_center = (workspace.width() - 32 - scaled_width)/2;
        ui.widget->setGeometry(horiz_center, 0, scaled_width, workspace.height()-32);

        adjuster.start(200);

        
        // Setup corresponding background picture
        QPixmap pixmap = thumbnails.front().scaledToWidth(workspace.width() - 32, Qt::SmoothTransformation);
        float upshift = -1.0f*(pixmap.height() - workspace.height())/2;
        if (is_label_two_next) {
            ui.label_2->setPixmap(pixmap);
            ui.label_2->setGeometry(0, upshift, pixmap.width(), pixmap.height());
            ui.label->lower();
            is_label_two_next = false;
        }
        else {
            ui.label->setPixmap(pixmap);
            ui.label->setGeometry(0, upshift, pixmap.width(), pixmap.height());
            ui.label_2->lower();
            is_label_two_next = true;
        }
        thumbnails.pop_front();
        show();
        player.setPosition(28000);
    }
}

void VideoFrame::play() {
    connect(KX11Extras::self(), &KX11Extras::windowAdded, this, &VideoFrame::handleAddedWindow);
    playlist.setCurrentIndex(0);
    player.play();
}

void VideoFrame::adjust_volume() {
        QStringList arguments_unmute;
        QStringList arguments_setvol;
        arguments_unmute << "sset" << "Master" << "unmute";
        arguments_setvol << "sset" << "Master" << "50%";
        volume_setter.start("amixer", arguments_unmute);
        volume_setter.waitForFinished();
        volume_setter.start("amixer", arguments_setvol);
        volume_setter.waitForFinished();
}
