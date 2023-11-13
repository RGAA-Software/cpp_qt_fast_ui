#include "avatar.h"

#include "settings.h"

Avatar::Avatar(int size, QWidget *parent) : QWidget(parent) {
    setFixedSize(QSize(size, size));
    QImage image;
    image.load(":/images/resources/avatar.png");
    pixmap_ = QPixmap::fromImage(image);
    pixmap_ = pixmap_.scaled(Settings::kAvatarSize, Settings::kAvatarSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void Avatar::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    QPen pen;
    pen.setColor(0x334466);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawEllipse(QRect(1, 1, this->rect().width()-2, this->rect().height()-2));
    //painter.setBrush(QBrush(0x334466));
    //painter.drawEllipse(this->rect());

    if (!pixmap_.isNull()) {
        painter.drawPixmap(0, 0, pixmap_);
    }
}
