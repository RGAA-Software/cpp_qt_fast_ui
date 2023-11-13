#include "content_page.h"

ContentPage::ContentPage(int item_count, int item_size, int padding_top, QWidget *parent)
    : QWidget(parent) {
    this->item_count_ = item_count;
    this->item_size_ = item_size;
    this->padding_top_ = padding_top;
}

void ContentPage::UpdateAudioItems(const std::vector<std::shared_ptr<AudioItem>>& items) {
    this->audio_items_ = items;
    repaint();
}

void ContentPage::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    painter.setBrush(QBrush(0xeeeeee));
    painter.setPen(Qt::NoPen);
    QRect inner_rect(0, 0, this->rect().width()-padding_size_ , this->rect().height()-padding_size_);
    painter.drawRect(inner_rect);

    painter.setBrush(QBrush(0x334466));

    // 1. horizontal gap
    int h_gap = (this->width() - this->item_size_*this->item_count_) / (this->item_count_+1);
    for (int audio_idx = 0; audio_idx < this->audio_items_.size(); audio_idx++) {
//        0 % 3 => 0
//        1 % 3 => 1
//        2 % 3 => 2
//        3 % 3 => 0
        int draw_idx = audio_idx % this->item_count_;
        int line_idx = audio_idx / this->item_count_;
        QRect item_rect(draw_idx*this->item_size_ + h_gap*(draw_idx+1), (padding_top_ + this->item_size_)*line_idx, item_size_, item_size_);
        painter.drawRect(item_rect);
    }
}
