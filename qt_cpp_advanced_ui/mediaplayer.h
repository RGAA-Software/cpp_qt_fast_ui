#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include "libvlcpp/vlcpp/vlc.hpp"

#include <QString>
#include <memory>

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

private:
    std::shared_ptr<VLC::Instance> instance_ = nullptr;
    std::shared_ptr<VLC::Media> media_ = nullptr;
    std::shared_ptr<VLC::MediaPlayer> player_ = nullptr;

};

#endif // MEDIAPLAYER_H
