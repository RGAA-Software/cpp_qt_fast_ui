#include "play_controller.h"

PlayController::PlayController(QWidget *parent) : QWidget(parent) {

}

void PlayController::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setBrush(QBrush(0xccddee));
    painter.drawRect(this->rect());
}
