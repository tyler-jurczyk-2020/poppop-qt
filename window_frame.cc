#include <QApplication>
#include <QTimer>
#include <QPushButton>
#include <QAbstractButton>
#include <QObject>
#include <QMetaMethod>
#include <QMainWindow>
#include <QObject>
#include <QLineEdit>
#include <qtmetamacros.h>
#include <random>
#include "ui_popup.h"
#include "window_frame.h"

void WindowFrame::grab_click() {
    close();
}

QPushButton &WindowFrame::get_button(){
    return *ui.pushButton;
}

WindowFrame::WindowFrame(std::mt19937 &random_seed, std::uniform_int_distribution<std::mt19937::result_type> generator) :
rng_w(std::random_device()()), rng_h(std::random_device()()),
dist_w(std::uniform_int_distribution<std::mt19937::result_type>(0,1550)),
dist_h(std::uniform_int_distribution<std::mt19937::result_type>(0,800)) {
    ui.setupUi(this); 

    int rnum = generator(random_seed);
    QString path = QString("../images/f_%1.jpg").arg(rnum);
    ui.label->setPixmap(QPixmap(path).scaledToHeight(500, Qt::SmoothTransformation));

    setGeometry(dist_w(rng_w), dist_h(rng_h), ui.label->sizeHint().width(), ui.label->sizeHint().height());
    setWindowFlags(Qt::FramelessWindowHint
                         | Qt::WindowStaysOnTopHint
                         | Qt::WindowDoesNotAcceptFocus);
    connect(ui.pushButton, &QPushButton::clicked, this, &WindowFrame::grab_click);
    show();
}

