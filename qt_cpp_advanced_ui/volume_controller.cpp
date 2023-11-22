#include "volume_controller.h"

#include <QPainterPath>

VolumeController::VolumeController(QWidget *parent) : QWidget(parent) {

}

void VolumeController::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);

    //painter.setBrush(QBrush(0xccddee));
    //painter.drawRect(this->rect());

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(0x334466));
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    QPainterPath path;
    path.moveTo(0, this->height()-1);
    path.lineTo(this->width()-1, this->height()-1);
    path.lineTo(this->width()-1, 0);
    path.lineTo(0, this->height()-1);
    painter.drawPath(path);

    painter.setBrush(QBrush(QColor(0x334466)));
    {
        float k = this->height() * 1.0f / this->width();
        int target_width = current_volume_*1.0f / 100.0f * this->width();
        int target_y = k * target_width;
        QPainterPath path;
        path.moveTo(0, this->height()-1);
        path.lineTo(target_width, this->height() - target_y);
        path.lineTo(target_width, this->height() - 0);
        path.lineTo(0, this->height()-1);
        painter.drawPath(path);
    }
}

void VolumeController::mousePressEvent(QMouseEvent *event) {

}

void VolumeController::mouseReleaseEvent(QMouseEvent *event) {
    int percent = event->pos().x() * 1.0f / this->width() * 100;
    SetCurrentVolume(percent);
    repaint();

    if (this->volume_cbk_) {
        this->volume_cbk_(percent);
    }
}

void VolumeController::SetCurrentVolume(int volume) {
    this->current_volume_ = volume;
    repaint();
}

void VolumeController::SetVolumeCallback(std::function<void(int)>&& cbk) {
    this->volume_cbk_ = std::move(cbk);
}







