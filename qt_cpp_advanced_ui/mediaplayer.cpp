#include "mediaplayer.h"

#include <QDebug>

MediaPlayer::MediaPlayer(const QString& name) {
    instance_ = std::make_shared<VLC::Instance>(0, nullptr);

    instance_->setExitHandler([]() {
        qDebug() << "exit ....";
    });

    instance_->logSet([](int level, const libvlc_log_t*, std::string message) {
        //std::cout << "vlc msg : " << message << std::endl;
    });

    media_ = std::make_shared<VLC::Media>(*instance_.get(), name.toStdString().c_str(), VLC::Media::FromPath);
    player_ = std::make_shared<VLC::MediaPlayer>(*media_.get());

    player_->eventManager().onOpening([=]() {
        qDebug() << "onOpening";
    });

    player_->eventManager().onPlaying([=]() {
        qDebug() << "onPlaying";
    });

    player_->eventManager().onPositionChanged([this](float pos) {
        //qDebug() << "onPositionChanged: " << pos;
        if (on_position_changed_cbk_) {
            on_position_changed_cbk_(pos);
        }
    });

    player_->eventManager().onTimeChanged([=](float t) {
        //qDebug() << "onTimeChanged: " << t;
    });

    player_->eventManager().onPaused([=]() {
        qDebug() << "onPaused ";
    });

    player_->eventManager().onStopped([=]() {
        qDebug() << "onStopped";
    });

    player_->eventManager().onEndReached([=]() {
        qDebug() << "onEndReached";
    });
}

MediaPlayer::~MediaPlayer() {

}


void MediaPlayer::Play() {
    player_->play();
}

void MediaPlayer::Pause() {
    player_->pause();
}

void MediaPlayer::Resume() {
    player_->setPause(false);
}

void MediaPlayer::Stop() {
    player_->stop();
}

void MediaPlayer::SetVolume(int volume) {
    player_->setVolume(volume);
}

void MediaPlayer::SeekPosition(float percent) {
    player_->setPosition(percent);
}

void MediaPlayer::SetOnPositionChangedCallback(std::function<void (float)> &&cbk) {
    on_position_changed_cbk_ = std::move(cbk);
}
