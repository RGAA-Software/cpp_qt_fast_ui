#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

#include <QPainter>

class SideBar : public QWidget
{
    Q_OBJECT
public:
    explicit SideBar(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

signals:

};

#endif // SIDEBAR_H
