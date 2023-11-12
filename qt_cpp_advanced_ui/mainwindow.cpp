#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>

#include "title_bar.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor(0x888888));
    shadow->setBlurRadius(10);
    this->setGraphicsEffect(shadow);

    auto root_layout = new QVBoxLayout();
    root_layout->setSpacing(0);
    root_layout->setMargin(0);
    title_bar_ = new TitleBar(this);
    root_layout->addSpacing(5);

    root_layout->addWidget(title_bar_);
    root_layout->addStretch();
    setLayout(root_layout);

    // title bar events
    title_bar_->SetMinClickCallback([=]() {
        this->showMinimized();
    });

    title_bar_->SetCloseClickCallback([=]() {
        qApp->exit(0);
    });
}

MainWindow::~MainWindow() {

}

void MainWindow::paintEvent(QPaintEvent *ev) {
    QPainter painter(this);
    int radius = 7;
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(0xffffff)));
    int padding = 5;
    QRect inner_rect(padding, padding, this->rect().width()-padding*2, this->rect().height()-padding*2);
    painter.drawRoundedRect(inner_rect, radius, radius);

}

void MainWindow::resizeEvent(QResizeEvent *event) {
    if (title_bar_) {
        title_bar_->setFixedWidth(event->size().width());
    }
}

