#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class Slider : public QWidget
{
    Q_OBJECT
public:
    Slider(int nc, int ac, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void SetCurrentProgress(int percent);

    void SetProgressCallback(std::function<void(float)>&& cbk);

private:

    int normal_color_;
    int active_color_;

    bool enter_ = false;
    bool mouse_pressed_ = false;

    int circle_handle_x_offset_ = 0;

    std::function<void(float)> progress_cbk_;

};

#endif // SLIDER_H
