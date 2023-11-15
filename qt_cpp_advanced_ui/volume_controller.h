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

private:

    int current_volume_ = 30;

};

#endif // VOLUMECONTROLLER_H
