#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>

#include "title_bar.h"
#include "side_bar.h"
#include "content_page.h"
#include "audio_item.h"
#include "settings.h"
#include "layout_helper.h"
#include "play_controller.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    auto shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor(0x666666));
    shadow->setBlurRadius(12);
    this->setGraphicsEffect(shadow);

    title_bar_ = new TitleBar(this);
    side_bar_ = new SideBar(this);
    play_controller_ = new PlayController();

    auto scroll_area_layout = new QVBoxLayout();
    LayoutHelper::ClearMarginSpacing(scroll_area_layout);

    content_area_ = new QScrollArea();
    scroll_area_layout->addWidget(content_area_);

    play_controller_->setFixedHeight(90);
    scroll_area_layout->addWidget(play_controller_);
    scroll_area_layout->addStretch();

    content_area_->setFixedHeight(400);
    content_area_->setStyleSheet("background-color:#ffffff; border:none;");
    content_page_ = new ContentPage(4, 140, 40, this);
    int real_content_width = Settings::kWindowWidth - Settings::kSideBarWidth - 5;
    content_area_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    content_area_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    content_area_->setWidget(content_page_);

    content_page_->setFixedWidth(real_content_width);
    content_page_->SetMarginTop(40);
    // test
    {
        std::vector<std::shared_ptr<AudioItem>> items;
        for (int i = 0; i < 20; i++) {
            items.push_back(AudioItem::Make("", "海浪之声"));
        }
        content_page_->UpdateAudioItems(items);
    }

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
    content_layout->addLayout(scroll_area_layout);

    root_layout->addLayout(content_layout);
    content_layout->addSpacing(5);
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
}

