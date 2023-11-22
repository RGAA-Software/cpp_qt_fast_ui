#include "slider.h"

#include <QDebug>

#include <algorithm>

Slider::Slider(int nc, int ac, QWidget *parent) : QWidget(parent) {
    this->normal_color_ = nc;
    this->active_color_ = ac;
    setMouseTracking(true);
}

void Slider::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);

    int circle_handle_radius = 6;
    int slider_height = 2;
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(normal_color_)));

    int slider_x_offset = 0;
    int slider_y_offset = (this->height() - slider_height)/2;
    painter.drawRect(slider_x_offset, slider_y_offset, this->width(), slider_height);

    painter.setBrush(QBrush(QColor(active_color_)));
    painter.drawRect(slider_x_offset, slider_y_offset, circle_handle_x_offset_, slider_height);

    QPen pen;
    pen.setColor(QColor(0xcccccc));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawEllipse(QPointF(circle_handle_x_offset_, this->height()/2), circle_handle_radius, circle_handle_radius);

}

void Slider::enterEvent(QEvent *event) {
    enter_ = true;
    repaint();
}

void Slider::leaveEvent(QEvent *event) {
    enter_ = false;
    repaint();
}

void Slider::mousePressEvent(QMouseEvent *event) {
    mouse_pressed_ = true;
    circle_handle_x_offset_ = event->pos().x();
    repaint();
}

void Slider::mouseMoveEvent(QMouseEvent *event) {
    if (mouse_pressed_) {
        circle_handle_x_offset_ = event->pos().x();
        repaint();

        if (progress_cbk_) {
            float percent = circle_handle_x_offset_ * 1.0f / this->width();
            progress_cbk_(percent);
        }
    }
}

void Slider::mouseReleaseEvent(QMouseEvent *event) {
    mouse_pressed_ = false;
    circle_handle_x_offset_ = event->pos().x();
    repaint();

    if (progress_cbk_) {
        float percent = circle_handle_x_offset_ * 1.0f / this->width();
        progress_cbk_(percent);
    }
}

void Slider::SetCurrentProgress(int percent) {
    percent = std::min(100, percent);
    circle_handle_x_offset_ = percent * 1.0f / 100.0f * this->width();
    repaint();
}

void Slider::SetProgressCallback(std::function<void(float)>&& cbk) {
    progress_cbk_ = cbk;
}
