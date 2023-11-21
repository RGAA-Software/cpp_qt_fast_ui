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

    });

    player_->eventManager().onPlaying([=]() {

    });

    player_->eventManager().onPositionChanged([](float pos) {

    });

    player_->eventManager().onTimeChanged([=](float t) {

    });

    player_->eventManager().onPaused([=]() {

    });

    player_->eventManager().onStopped([=]() {

    });

    player_->eventManager().onEndReached([=]() {

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
