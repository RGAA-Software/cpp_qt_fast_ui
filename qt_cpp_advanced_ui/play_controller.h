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

signals:

private:

    RotateCover* rotate_cover_ = nullptr;
    QLabel* title_ = nullptr;
    Slider* slider_ = nullptr;
    CircleButton* play_btn_ = nullptr;
    VolumeController* volume_controller_ = nullptr;

    bool is_playing_ = false;
};

#endif // PLAYCONTROLLER_H
