#ifndef AVATAR_H
#define AVATAR_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QImage>

class Avatar : public QWidget
{
    Q_OBJECT
public:
    explicit Avatar(int size, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

signals:

private:

    QPixmap pixmap_;

};

#endif // AVATAR_H
