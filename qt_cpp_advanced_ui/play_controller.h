#ifndef PLAYCONTROLLER_H
#define PLAYCONTROLLER_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class RotateCover;

class PlayController : public QWidget
{
    Q_OBJECT
public:
    explicit PlayController(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

signals:

private:

    RotateCover* rotate_cover_ = nullptr;

};

#endif // PLAYCONTROLLER_H
