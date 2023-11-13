#include "avatar.h"

Avatar::Avatar(int size, QWidget *parent) : QWidget(parent) {
    setFixedSize(QSize(size, size));
}

void Avatar::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(0x334466));
    painter.drawEllipse(this->rect());
}
