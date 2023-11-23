#ifndef PLAYCONTROLLER_H
#define PLAYCONTROLLER_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>

class RotateCover;
class Slider;
class CircleButton;
class VolumeController;
class MediaPlayer;

class PlayController : public QWidget
{
    Q_OBJECT
public:
    explicit PlayController(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void UpdatePlayingPosition(float percent);
    void SetVolume(int volume);
    void SetTitle(const QString& title);
    void ChangeIcon(const QPixmap& pixmap);

    void SetMediaPlayer(const std::shared_ptr<MediaPlayer>& player);
    void ChangePlayButtonState(bool playing);

private:

    RotateCover* rotate_cover_ = nullptr;
    QLabel* title_ = nullptr;
    Slider* slider_ = nullptr;
    CircleButton* play_btn_ = nullptr;
    VolumeController* volume_controller_ = nullptr;

    bool is_playing_ = false;

    std::weak_ptr<MediaPlayer> media_player_;
};

#endif // PLAYCONTROLLER_H
