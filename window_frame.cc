#include "window_frame.h"
#include <memory>

void WindowFrame::grab_click() {
    emit received_button_push(wid);
}

void WindowFrame::set_window_id(WId id) {
    wid = id;
}

WindowFrame::WindowFrame(rngen &rngen, uniform_dist &image, uniform_dist &width, uniform_dist &height) :
rng(rngen), image_dist(image), width_dist(width), height_dist(height) {
    ui.setupUi(this); 

    int rnum = image_dist(rng);
    QString path = QString("../images/f_%1.jpg").arg(rnum);
    ui.label->setPixmap(QPixmap(path).scaledToHeight(500, Qt::SmoothTransformation));

    setGeometry(width_dist(rng), height_dist(rng), ui.label->sizeHint().width(), ui.label->sizeHint().height());
    setWindowTitle("poppop");
    connect(ui.pushButton, &QPushButton::clicked, this, &WindowFrame::grab_click);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
    show();
}

