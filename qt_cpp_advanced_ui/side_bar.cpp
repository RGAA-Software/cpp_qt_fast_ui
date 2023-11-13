#include "side_bar.h"
#include "settings.h"
#include "layout_helper.h"
#include "avatar.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

SideBarItem::SideBarItem(int nc, int ec, QWidget* parent) : QWidget(parent) {
    this->normal_color_ = nc;
    this->enter_color_ = ec;
}

void SideBarItem::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    painter.setPen(Qt::NoPen);
    if (enter_) {
        painter.setBrush(QBrush(this->enter_color_));
    }
    else {
        painter.setBrush(QBrush(this->normal_color_));
    }

    QRect inner_rect(left_right_padding_, 0, this->rect().width()-left_right_padding_*2, this->rect().height());
    painter.drawRoundedRect(inner_rect, this->height()/2, this->height()/2);

}

void SideBarItem::enterEvent(QEvent *event) {
    enter_ = true;
    repaint();
}

void SideBarItem::leaveEvent(QEvent *event) {
    enter_ = false;
    repaint();
}

void SideBarItem::mousePressEvent(QMouseEvent *event) {
    pressed_ = true;
    repaint();
}

void SideBarItem::mouseReleaseEvent(QMouseEvent *event) {
    pressed_ = false;
    repaint();
}

void SideBarItem::SetOnClickCallback(SideBarItemClickCallback&& cbk) {
    this->click_cbk_ = std::move(cbk);
}

//// ---------------------------------- ////

SideBar::SideBar(QWidget *parent) : QWidget(parent) {
    this->setFixedSize(QSize(Settings::kSideBarWidth, 530));

    auto root_layout = new QHBoxLayout();
    LayoutHelper::ClearMarginSpacing(root_layout);

    root_layout->addStretch();

    // item layout
    auto item_layout = new QVBoxLayout();
    LayoutHelper::ClearMarginSpacing(item_layout);
    // avatar
    {
        auto avatar = new Avatar(Settings::kAvatarSize, this);
        auto avatar_layout = new QHBoxLayout();
        LayoutHelper::ClearMarginSpacing(avatar_layout);
        avatar_layout->addStretch();
        avatar_layout->addWidget(avatar);
        avatar_layout->addStretch();
        item_layout->addSpacing(30);
        item_layout->addLayout(avatar_layout);
    }

    item_layout->addSpacing(30);
    {
        auto item = new SideBarItem(Settings::kSideBarNormalColor, Settings::kSideBarEnterColor, this);
        item->setFixedSize(QSize(Settings::kSideBarWidth, 35));
        item_layout->addWidget(item);
    }
    {
        auto item = new SideBarItem(Settings::kSideBarNormalColor, Settings::kSideBarEnterColor, this);
        item->setFixedSize(QSize(Settings::kSideBarWidth, 35));
        item_layout->addWidget(item);
    }
    {
        auto item = new SideBarItem(Settings::kSideBarNormalColor, Settings::kSideBarEnterColor, this);
        item->setFixedSize(QSize(Settings::kSideBarWidth, 35));
        item_layout->addWidget(item);
    }
    {
        auto item = new SideBarItem(Settings::kSideBarNormalColor, Settings::kSideBarEnterColor, this);
        item->setFixedSize(QSize(Settings::kSideBarWidth, 35));
        item_layout->addWidget(item);
    }
    item_layout->addStretch();

    root_layout->addLayout(item_layout);

    root_layout->addStretch();
    setLayout(root_layout);
}

void SideBar::paintEvent(QPaintEvent *event) {
#if 0
    QPainter painter(this);
    painter.setBrush(QBrush(0x009988));
    painter.drawRect(this->rect());
#endif
}
