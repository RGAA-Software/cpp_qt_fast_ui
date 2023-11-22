#ifndef VOLUMECONTROLLER_H
#define VOLUMECONTROLLER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class VolumeController : public QWidget
{
    Q_OBJECT
public:
    explicit VolumeController(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void SetCurrentVolume(int volume);

    void SetVolumeCallback(std::function<void(int)>&& cbk);

private:

    int current_volume_ = 30;

    std::function<void(int)> volume_cbk_;

};

#endif // VOLUMECONTROLLER_H
