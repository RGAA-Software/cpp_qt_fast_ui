#include "side_bar.h"
#include "settings.h"
#include "layout_helper.h"
#include "avatar.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

SideBarItem::SideBarItem(int nc, int ec, const QString& title, QWidget* parent) : QWidget(parent) {
    this->normal_color_ = nc;
    this->enter_color_ = ec;
    this->title_ = title;
}

void SideBarItem::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    painter.setPen(Qt::NoPen);
    if (enter_ || selected_) {
        painter.setBrush(QBrush(this->enter_color_));
    }
    else {
        painter.setBrush(QBrush(this->normal_color_));
    }

    QRect inner_rect(left_right_padding_, 0, this->rect().width()-left_right_padding_*2, this->rect().height());
    painter.drawRoundedRect(inner_rect, this->height()/2, this->height()/2);

    QPen pen;
    QFont font = QFont("Microsoft YaHei", 13, QFont::Bold, false);;
    if (enter_ || selected_) {
        pen.setColor(this->normal_color_);
    }
    else {
        pen.setColor(this->enter_color_);
    }
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(this->rect(), Qt::AlignCenter, title_);
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
    if (this->click_cbk_) {
        this->click_cbk_();
    }
}

void SideBarItem::SetOnClickCallback(SideBarItemClickCallback&& cbk) {
    this->click_cbk_ = std::move(cbk);
}

void SideBarItem::Select() {
    selected_ = true;
    repaint();
}

void SideBarItem::Unselect() {
    selected_ = false;
    repaint();
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
        auto item = new SideBarItem(Settings::kSideBarNormalColor, Settings::kSideBarEnterColor, "睡眠", this);
        item->setFixedSize(QSize(Settings::kSideBarWidth, 35));
        item_layout->addWidget(item);
        side_bar_items_.push_back(item);
        item->SetOnClickCallback([=]() {
            Select(0);
        });
    }
    {
        auto item = new SideBarItem(Settings::kSideBarNormalColor, Settings::kSideBarEnterColor, "专注",this);
        item->setFixedSize(QSize(Settings::kSideBarWidth, 35));
        item_layout->addSpacing(5);
        item_layout->addWidget(item);
        side_bar_items_.push_back(item);
        item->SetOnClickCallback([=]() {
            Select(1);
        });
    }
    {
        auto item = new SideBarItem(Settings::kSideBarNormalColor, Settings::kSideBarEnterColor, "放松", this);
        item->setFixedSize(QSize(Settings::kSideBarWidth, 35));
        item_layout->addSpacing(5);
        item_layout->addWidget(item);
        side_bar_items_.push_back(item);
        item->SetOnClickCallback([=]() {
            Select(2);
        });
    }
    {
        auto item = new SideBarItem(Settings::kSideBarNormalColor, Settings::kSideBarEnterColor, "冥想", this);
        item->setFixedSize(QSize(Settings::kSideBarWidth, 35));
        item_layout->addSpacing(5);
        item_layout->addWidget(item);
        side_bar_items_.push_back(item);
        item->SetOnClickCallback([=]() {
            Select(3);
        });
    }
    item_layout->addStretch();

    root_layout->addLayout(item_layout);

    root_layout->addStretch();
    setLayout(root_layout);

    // logic here
    Select(0);
}

void SideBar::paintEvent(QPaintEvent *event) {
#if 0
    QPainter painter(this);
    painter.setBrush(QBrush(0x009988));
    painter.drawRect(this->rect());
#endif
}

void SideBar::Select(int idx) {
    if (idx < 0 || idx >= side_bar_items_.size()) {
        return;
    }

    for (int i = 0; i < side_bar_items_.size(); i++) {
        if (i == idx) {
            side_bar_items_[i]->Select();
        }
        else {
            side_bar_items_[i]->Unselect();
        }
    }
}
