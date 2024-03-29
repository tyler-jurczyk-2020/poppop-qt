#include "video_frame.h"
#include <QAudioDeviceInfo>
#include <KX11Extras>
#include <memory>
#include <vector>

VideoFrame::VideoFrame() {
    ui.setupUi(this);
    QRect workspace = KX11Extras::workArea();
    setGeometry(16, 16, workspace.width() - 32, workspace.height() - 32);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
    setWindowTitle("poppop");
    ui.widget->raise();
    // Set blurring
    blur.setBlurRadius(100);
    blur2.setBlurRadius(100);
    ui.label->setGraphicsEffect(&blur);
    ui.label_2->setGraphicsEffect(&blur2);

    player.setVideoOutput(ui.widget);
    player.setPlaylist(&playlist);

    //Enable Audio
    player.setVolume(100);

    // Setup double buffered backgrounds
    is_label_two_next = true;

    connect(&adjuster, &QTimer::timeout, this, &VideoFrame::adjust_volume);

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

        if(!is_video) { 
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
        }
        show();
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

void VideoFrame::set_video(int video) {
    is_video = true;
    playlist.clear();
    QString current_video = QString("/home/tysonthebison/.config/systemd/poppop-qt/videos/f_%1.mp4").arg(video);
    playlist.addMedia(QUrl::fromLocalFile(current_video));
}

void VideoFrame::set_gifs(std::vector<int> gifs) {
    is_video = false;
    playlist.clear();
    thumbnails.clear();
    for(auto &gif : gifs) {
        QString current_gif = QString("/home/tysonthebison/.config/systemd/poppop-qt/gifs/f_%1.mp4").arg(gif);
        playlist.addMedia(QUrl::fromLocalFile(current_gif));
        QString current_thumb = QString("/home/tysonthebison/.config/systemd/poppop-qt/gifs/thumbnails/f_%1.jpg").arg(gif);
        thumbnails.emplace_back(current_thumb);
    }
}
