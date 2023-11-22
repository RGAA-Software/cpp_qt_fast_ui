#include "rotate_cover.h"

RotateCover::RotateCover(int size, const QString& url, QWidget *parent) : QWidget(parent) {
    setFixedSize(QSize(size, size));

    QImage image;
    image.load(url);
    pixmap_ = QPixmap::fromImage(image);
    pixmap_ = pixmap_.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    rotate_timer_ = new QTimer(this);
    connect(rotate_timer_, &QTimer::timeout, this, [=]() {
        rotate_angel_ += 0.8f;
        repaint();
    });
    rotate_timer_->start(17);
}

void RotateCover::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    int pen_width = 4;
    QPen pen;
    pen.setWidth(pen_width);
    pen.setColor(QColor(0x334466));
    painter.setPen(pen);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);

    painter.save();
    painter.translate(this->width()/2, this->height()/2);
    painter.rotate(rotate_angel_);

    QPainterPath path;
    QRect circle_image_rect;
    circle_image_rect.setX(-this->width()/2);
    circle_image_rect.setY(-this->width()/2);
    circle_image_rect.setWidth(this->width());
    circle_image_rect.setHeight(this->height());
    path.addRoundedRect(circle_image_rect, this->width()/2, this->height()/2);
    painter.setClipPath(path);
    painter.drawPixmap(-this->width()/2, -this->width()/2, pixmap_);
    painter.restore();

    QRect border_rect(pen_width/2, pen_width/2, this->width()-pen_width, this->height()-pen_width);
    painter.drawRoundedRect(border_rect, border_rect.width()/2, border_rect.height()/2);

    int inner_circle_width = 12;
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(0xffffff)));
    painter.drawEllipse(QPointF(this->width()/2, this->height()/2), inner_circle_width, inner_circle_width);

}

void RotateCover::ChangeIcon(const QPixmap& pixmap) {
    pixmap_ = pixmap;
}
