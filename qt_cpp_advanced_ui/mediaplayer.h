#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include "libvlcpp/vlcpp/vlc.hpp"

#include <QString>
#include <memory>
#include <functional>

class MediaPlayer
{
public:
    MediaPlayer(const QString& name);
    ~MediaPlayer();

    void Play();
    void Pause();
    void Resume();
    void Stop();
    void SetVolume(int volume);
    void SeekPosition(float percent);

    void SetOnPositionChangedCallback(std::function<void(float)>&& cbk);

private:
    std::shared_ptr<VLC::Instance> instance_ = nullptr;
    std::shared_ptr<VLC::Media> media_ = nullptr;
    std::shared_ptr<VLC::MediaPlayer> player_ = nullptr;

    std::function<void(float)> on_position_changed_cbk_ = nullptr;
};

#endif // MEDIAPLAYER_H
