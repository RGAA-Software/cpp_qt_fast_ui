#ifndef CIRCLEBUTTON_H
#define CIRCLEBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QString>

#include <functional>

using OnButtonClickCallback = std::function<void()>;

class CircleButton : public QWidget
{
    Q_OBJECT
public:
    explicit CircleButton(const QString& icon_url, const QString& active_icon_url = "", QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void SetOnClickCallback(OnButtonClickCallback&& cbk);
    void ChangeIcon(const QString& icon_url, const QString& active_icon_url = "");

signals:

private:

    bool enter_ = false;

    QPixmap pixmap_;
    QPixmap pixmap_active_;

    OnButtonClickCallback callback_;

};

#endif // CIRCLEBUTTON_H
