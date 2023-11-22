#include "play_controller.h"
#include "rotate_cover.h"
#include "layout_helper.h"
#include "slider.h"
#include "circle_button.h"
#include "volume_controller.h"
#include "mediaplayer.h"

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

        root_layout->addSpacing(20);
        root_layout->addLayout(item_layout);
    }
    {
        auto item_layout = new QVBoxLayout();
        LayoutHelper::ClearMarginSpacing(item_layout);
        title_ = new QLabel();
        title_->setText("海浪之声");
        title_->setStyleSheet("font-family:Microsoft YaHei; font-size: 15px; font-weight: bold;");
        item_layout->addSpacing(15);
        item_layout->addWidget(title_);

        slider_ = new Slider(0xbbbbbb, 0x334466, this);
        slider_->setFixedHeight(30);
        slider_->setMinimumWidth(450);
        slider_->SetCurrentProgress(50);
        slider_->SetProgressCallback([=](float percent) {
            auto mp = this->media_player_.lock();
            if (mp) {
                mp->SeekPosition(percent);
            }
        });
        item_layout->addSpacing(10);
        item_layout->addWidget(slider_);

        item_layout->addStretch();

        root_layout->addSpacing(20);
        root_layout->addLayout(item_layout);
    }

    {
        auto item_layout = new QVBoxLayout();
        LayoutHelper::ClearMarginSpacing(item_layout);

        play_btn_ = new CircleButton(":/images/resources/play_arrow.svg", ":/images/resources/play_arrow_active.svg");
        play_btn_->setFixedSize(QSize(30, 30));
        play_btn_->SetOnClickCallback([=]() {
            if (is_playing_) {
                is_playing_ = false;
                play_btn_->ChangeIcon(":/images/resources/play_arrow.svg", ":/images/resources/play_arrow_active.svg");
                auto mp = this->media_player_.lock();
                if (mp) {
                    mp->Pause();
                }
            }
            else {
                is_playing_ = true;
                play_btn_->ChangeIcon(":/images/resources/pause.svg", ":/images/resources/pause_active.svg");
                auto mp = this->media_player_.lock();
                if (mp) {
                    mp->Resume();
                }
            }
        });

        item_layout->addStretch();
        item_layout->addWidget(play_btn_);
        item_layout->addStretch();

        root_layout->addSpacing(25);
        root_layout->addLayout(item_layout);
    }

    {
        auto item_layout = new QVBoxLayout();
        LayoutHelper::ClearMarginSpacing(item_layout);

        volume_controller_ = new VolumeController(this);
        volume_controller_->setFixedSize(QSize(100, 25));
        volume_controller_->SetVolumeCallback([this](int percent) {
            auto mp = this->media_player_.lock();
            if (mp) {
                mp->SetVolume(percent);
            }
        });
        item_layout->addSpacing(32);
        item_layout->addWidget(volume_controller_);
        item_layout->addStretch();

        root_layout->addSpacing(25);
        root_layout->addLayout(item_layout);
    }

    root_layout->addStretch();

    setLayout(root_layout);
}

void PlayController::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(0xccddee));
    //painter.drawRect(this->rect());
}

void PlayController::UpdatePlayingPosition(float percent) {
    slider_->SetCurrentProgress(percent * 100);
}

void PlayController::SetVolume(int volume) {
    volume_controller_->SetCurrentVolume(volume);
}

void PlayController::SetTitle(const QString& title) {
    title_->setText(title);
}

void PlayController::ChangeIcon(const QPixmap& pixmap) {
    rotate_cover_->ChangeIcon(pixmap);
}

void PlayController::SetMediaPlayer(const std::shared_ptr<MediaPlayer>& player) {
    media_player_ = player;
}

