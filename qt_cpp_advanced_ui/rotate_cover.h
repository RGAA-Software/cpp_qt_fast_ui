#ifndef ROTATECOVER_H
#define ROTATECOVER_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QTimer>

class RotateCover : public QWidget
{
    Q_OBJECT
public:
    explicit RotateCover(int size, const QString& url, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

signals:

private:

    QPixmap pixmap_;
    QTimer* rotate_timer_ = nullptr;
    float rotate_angel_ = 0;

};

#endif // ROTATECOVER_H
