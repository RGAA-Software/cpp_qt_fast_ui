#include "title_bar.h"
#include "settings.h"

#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

OperationIcon::OperationIcon(int radius, int normal_color, int enter_color, QWidget* parent) : QWidget(parent) {
    this->radius_ = radius;
    this->normal_color_ = normal_color;
    this->enter_color_ = enter_color;
}

void OperationIcon::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    painter.setPen(Qt::NoPen);
    if (enter_) {
        painter.setBrush(QBrush(QColor(this->enter_color_)));
    }
    else {
        painter.setBrush(QBrush(QColor(this->normal_color_)));
    }
    painter.drawRoundedRect(this->rect(), this->width()/2, this->height()/2);
}

void OperationIcon::enterEvent(QEvent *event) {
   enter_ = true;
   repaint();
}

void OperationIcon::leaveEvent(QEvent* event) {
    enter_ = false;
    repaint();
}

void OperationIcon::mousePressEvent(QMouseEvent *event) {
    pressed_ = true;
    repaint();
}

void OperationIcon::mouseReleaseEvent(QMouseEvent *event) {
    pressed_ = false;
    repaint();

    if (click_cbk_) {
        click_cbk_();
    }
}

void OperationIcon::SetOnClickCallback(ClickCallback&& cbk) {
    click_cbk_ = std::move(cbk);
}

///// ------------------------------------------------------////

TitleBar::TitleBar(QWidget* parent) : QWidget(parent) {
    setFixedHeight(Settings::kTitleBarHeight);
    auto root_layout = new QVBoxLayout();

    auto item_layout = new QHBoxLayout();
    item_layout->addStretch();

    auto btn_size = Settings::kOperationBtnRadius;

    // min
    {
        auto min_btn = new OperationIcon(btn_size,
                                         Settings::kOperationBtnMinNomralColor,
                                         Settings::kOperationBtnMinEnterColor,
                                         this);
        min_btn->setFixedSize(QSize(btn_size, btn_size));
        min_btn->SetOnClickCallback([=]() { min_click_cbk_(); });
        item_layout->addWidget(min_btn);
    }
    item_layout->addSpacing(6);

    // close
    {
        auto close_btn = new OperationIcon(btn_size,
                                           Settings::kOperationBtnCloseNomralColor,
                                           Settings::kOperationBtnCloseEnterColor,
                                           this);
        close_btn->setFixedSize(QSize(btn_size, btn_size));
        close_btn->SetOnClickCallback([=]() {close_click_cbk_();});
        item_layout->addWidget(close_btn);
    }
    item_layout->addSpacing(6);

    root_layout->addLayout(item_layout);

    setLayout(root_layout);
}

TitleBar::~TitleBar() {

}

void TitleBar::paintEvent(QPaintEvent *event) {
#if 0
    QPainter painter(this);
    painter.setBrush(QBrush(0x0099ff));
    painter.drawRect(this->rect());
#endif
}

void TitleBar::SetMinClickCallback(ClickCallback&& cbk) {
    min_click_cbk_ = cbk;
}

void TitleBar::SetCloseClickCallback(ClickCallback&& cbk) {
    close_click_cbk_  = cbk;
}

void TitleBar::mousePressEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        click_point_ = event->globalPos();
        click_window_pos_ = mapToGlobal(pos());
        //qDebug() << "click point : " << event->pos();
        left_pressed_ = true;
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) && left_pressed_) {
        QPoint point_offset = event->globalPos() - click_point_;
        ((QWidget*)this->parent())->move(click_window_pos_ + point_offset);
        //qDebug() << "move point : " << event->pos();
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event) {
    left_pressed_ = false;
}
