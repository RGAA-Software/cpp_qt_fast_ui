#include "play_controller.h"
#include "rotate_cover.h"
#include "layout_helper.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

PlayController::PlayController(QWidget *parent) : QWidget(parent) {
    auto root_layout = new QHBoxLayout();
    LayoutHelper::ClearMarginSpacing(root_layout);

    root_layout->addSpacing(2);
    {
        auto item_layout = new QVBoxLayout();
        LayoutHelper::ClearMarginSpacing(item_layout);
        rotate_cover_ = new RotateCover(60, ":/images/resources/preset_1.jpg", this);
        item_layout->addStretch();
        item_layout->addWidget(rotate_cover_);
        item_layout->addStretch();
        root_layout->addLayout(item_layout);
    }
    {

    }

    root_layout->addStretch();

    setLayout(root_layout);
}

void PlayController::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(0xccddee));
    painter.drawRect(this->rect());
}
