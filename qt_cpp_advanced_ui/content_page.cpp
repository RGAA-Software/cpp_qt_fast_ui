#include "content_page.h"
#include "audio_item.h"

#include <QDebug>

ContentPage::ContentPage(int item_count, int item_size, int padding_top, QWidget *parent)
    : QWidget(parent) {
    this->item_count_ = item_count;
    this->item_size_ = item_size;
    this->padding_top_ = padding_top;

    setMouseTracking(true);
}

void ContentPage::UpdateAudioItems(const std::vector<std::shared_ptr<AudioItem>>& items) {
    this->audio_items_ = items;
    int line_count = items.size() / this->item_count_;
    int total_height = margin_top_ + line_count*(this->item_size_ + this->padding_top_) + this->margin_top_;// another margin_top_ for bottom...
    setFixedHeight(total_height);

    repaint();
}

void ContentPage::SetMarginTop(int mt) {
    this->margin_top_ = mt;
}

void ContentPage::mousePressEvent(QMouseEvent *event) {
    current_mouse_pos_ = event->pos();
    repaint();
}

void ContentPage::mouseMoveEvent(QMouseEvent *event) {
    current_mouse_pos_ = event->pos();
    repaint();
}

void ContentPage::mouseReleaseEvent(QMouseEvent *event) {

    repaint();
}

void ContentPage::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    painter.setBrush(QBrush(0xeeeeee));
    painter.setPen(Qt::NoPen);
    QRect inner_rect(0, 0, this->rect().width()-padding_size_ , this->rect().height()-padding_size_);
    //painter.drawRect(inner_rect);

    // 1. horizontal gap
    int h_gap = (this->width() - this->item_size_*this->item_count_) / (this->item_count_+1);
    for (int audio_idx = 0; audio_idx < this->audio_items_.size(); audio_idx++) {
        auto& item = audio_items_[audio_idx];
//        0 % 3 => 0
//        1 % 3 => 1
//        2 % 3 => 2
//        3 % 3 => 0
        int draw_idx = audio_idx % this->item_count_;
        int line_idx = audio_idx / this->item_count_;
        QRect item_rect(draw_idx*this->item_size_ + h_gap*(draw_idx+1),
                        (padding_top_ + this->item_size_)*line_idx + this->margin_top_,
                        item_size_, item_size_);
        item->draw_rect_ = item_rect;
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(0xddddee));
        if (item->draw_rect_.contains(current_mouse_pos_)) {
            painter.drawRoundedRect(item_rect, 10, 10);
            current_item_ = item;
        }

        int circle_diameter = item_rect.width()* 0.7;
        int left_padding = (item_rect.width() - circle_diameter)/2;
        QRect circle_rect(item_rect.x() + left_padding,
                          item_rect.y() + 7,
                          circle_diameter,
                          circle_diameter);
        painter.setBrush(QBrush(0xffffff));
        painter.drawEllipse(circle_rect);

        painter.save();
        QPainterPath path;
        int circle_x_offset = item_rect.x() + left_padding;
        int circle_y_offset = item_rect.y() + 7;
        QRect circle_path_rect(circle_x_offset, circle_y_offset, circle_diameter, circle_diameter);
//        mask_rect.setX();
//        mask_rect.setY(item_rect.y() + 7);
        path.addRoundedRect(circle_path_rect, circle_diameter/2, circle_diameter/2);
        painter.setClipPath(path);
        painter.drawPixmap(item_rect.x() + left_padding, item_rect.y() + 7, item->pixmap_);
        painter.restore();

        QPen pen;
        QFont font("Microsoft YaHei", 13, QFont::Normal, false);
        painter.setFont(font);
        painter.setPen(pen);
        int font_region_height = 33;
        QRect font_rect(item_rect.x(), item_rect.y() + item_size_ - font_region_height, item_size_, font_region_height);
        painter.drawText(font_rect, Qt::AlignHCenter|Qt::AlignVCenter, item->name_);
    }
}
