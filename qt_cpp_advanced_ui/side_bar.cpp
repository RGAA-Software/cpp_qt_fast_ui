#include "side_bar.h"

#include "settings.h"

SideBar::SideBar(QWidget *parent) : QWidget(parent) {
    this->setFixedSize(QSize(Settings::kSideBarWidth, 530));
}

void SideBar::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setBrush(QBrush(0x009988));
    painter.drawRect(this->rect());
}
