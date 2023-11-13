#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>

#include "title_bar.h"
#include "side_bar.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor(0x666666));
    shadow->setBlurRadius(12);
    this->setGraphicsEffect(shadow);

    title_bar_ = new TitleBar(this);
    side_bar_ = new SideBar(this);

    auto root_layout = new QVBoxLayout();
    root_layout->setSpacing(0);
    root_layout->setMargin(0);
    root_layout->addSpacing(5);

    root_layout->addWidget(title_bar_);

    // content
    auto content_layout = new QHBoxLayout();
    content_layout->setSpacing(0);
    content_layout->setMargin(0);
    content_layout->addSpacing(5);
    content_layout->addWidget(side_bar_);
    content_layout->addStretch();
    root_layout->addLayout(content_layout);

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
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    int radius = 10;
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
    if (side_bar_) {

    }
}

