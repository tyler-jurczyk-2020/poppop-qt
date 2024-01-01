#include "window_frame.h"

void WindowFrame::grab_click() {
    close();
}

QPushButton &WindowFrame::get_button(){
    return *ui.pushButton;
}

WindowFrame::WindowFrame(rngen &rngen, uniform_dist &image, uniform_dist &width, uniform_dist &height) :
rng(rngen), image_dist(image), width_dist(width), height_dist(height) {
    ui.setupUi(this); 

    int rnum = image_dist(rng);
    QString path = QString("../images/f_%1.jpg").arg(rnum);
    ui.label->setPixmap(QPixmap(path).scaledToHeight(500, Qt::SmoothTransformation));

    setGeometry(width_dist(rng), height_dist(rng), ui.label->sizeHint().width(), ui.label->sizeHint().height());
    setWindowFlags(Qt::FramelessWindowHint
                         | Qt::WindowStaysOnTopHint
                         | Qt::WindowDoesNotAcceptFocus);
    connect(ui.pushButton, &QPushButton::clicked, this, &WindowFrame::grab_click);
    show();
}

