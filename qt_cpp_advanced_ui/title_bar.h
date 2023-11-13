#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

using ClickCallback = std::function<void()>;

class OperationIcon : public QWidget {
public:

    OperationIcon(int radius, int normal_color, int enter_color, QWidget* parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void SetOnClickCallback(ClickCallback&& cbk);

private:

    int radius_ = 10;
    int normal_color_ = 0xff0099;
    int enter_color_ = 0xff000000;

    bool enter_ = false;
    bool pressed_ = false;

    ClickCallback click_cbk_;

};

class TitleBar : public QWidget
{
public:
    TitleBar(QWidget* parent = nullptr);
    ~TitleBar();

    void paintEvent(QPaintEvent *event) override;

    void SetMinClickCallback(ClickCallback&& cbk);
    void SetCloseClickCallback(ClickCallback&& cbk);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:

    ClickCallback min_click_cbk_;
    ClickCallback close_click_cbk_;

    QPoint click_point_{};
    QPoint click_window_pos_{};
    bool left_pressed_ = false;

};

#endif // TITLEBAR_H
