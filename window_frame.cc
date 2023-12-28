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

WindowFrame::WindowFrame(std::mt19937 random_seed, std::uniform_int_distribution<std::mt19937::result_type> generator){
    ui.setupUi(this); 
    int rnum = generator(random_seed);
    setWindowFlags(Qt::FramelessWindowHint
                         | Qt::WindowStaysOnTopHint
                         | Qt::WindowDoesNotAcceptFocus);
    QString path = QString("../images/f_%1.jpg").arg(rnum);
    ui.label->setPixmap(QPixmap(path).scaledToHeight(500, Qt::SmoothTransformation));
    setGeometry(1550, 800, ui.label->sizeHint().width(), ui.label->sizeHint().height());
    connect(ui.pushButton, &QPushButton::clicked, this, &WindowFrame::grab_click);
    show();
}

