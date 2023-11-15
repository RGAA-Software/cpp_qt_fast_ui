#include "circle_button.h"

CircleButton::CircleButton(const QString& icon_url, const QString& active_icon_url, QWidget *parent) : QWidget(parent) {
    this->ChangeIcon(icon_url, active_icon_url);
}

void CircleButton::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);

    int pen_width = 1;
    QPen pen;
    pen.setWidth(1);
    if (enter_) {
        pen.setColor(QColor(0x334466));

        painter.setBrush(QBrush(QColor(0x334466)));
    }
    else {
        pen.setColor(QColor(0xcccccc));

        painter.setBrush(Qt::NoBrush);
    }
    painter.setPen(pen);

    int radius = (this->width()-2*pen_width)/2;
    painter.drawEllipse(QPointF(this->width()/2, this->height()/2), radius, radius);

    if (enter_ && !pixmap_active_.isNull()) {
        painter.drawPixmap((this->width() - pixmap_.width())/2, (this->height() - pixmap_.height())/2, pixmap_);
    } else {
        painter.drawPixmap((this->width() - pixmap_active_.width())/2, (this->height() - pixmap_active_.height())/2, pixmap_active_);
    }

}

void CircleButton::enterEvent(QEvent *event) {
    enter_ = true;
    repaint();
}

void CircleButton::leaveEvent(QEvent *event) {
    enter_ = false;
    repaint();
}

void CircleButton::mouseReleaseEvent(QMouseEvent *event) {
    if (callback_) {
        callback_();
    }
    repaint();
}

void CircleButton::SetOnClickCallback(OnButtonClickCallback&& cbk) {
    this->callback_ = std::move(cbk);
}

void CircleButton::ChangeIcon(const QString& icon_url, const QString& active_icon_url) {
    QImage image;
    image.load(icon_url);
    pixmap_ = QPixmap::fromImage(image);
    pixmap_ = pixmap_.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    if (!active_icon_url.isEmpty()) {
        QImage image;
        image.load(active_icon_url);
        pixmap_active_ = QPixmap::fromImage(image);
        pixmap_active_ = pixmap_active_.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    repaint();
}
