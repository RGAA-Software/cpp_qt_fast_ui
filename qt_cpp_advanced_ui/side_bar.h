#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QPainter>
#include <functional>

using SideBarItemClickCallback = std::function<void()>;

class SideBarItem : public QWidget {
public:
    SideBarItem(int nc, int ec, QWidget* parent = nullptr);
    ~SideBarItem() = default;

    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void SetOnClickCallback(SideBarItemClickCallback&& cbk);
    void Select();
    void Unselect();

private:
    SideBarItemClickCallback click_cbk_;

    int normal_color_ = 0xcc0000;
    int enter_color_ = 0xdd0000;

    bool enter_ = false;
    bool pressed_ = false;

    int left_right_padding_ = 8;

    bool selected_ = false;
};

//// ---------------------------------------- ////

class SideBar : public QWidget
{
    Q_OBJECT
public:
    explicit SideBar(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void Select(int idx);

signals:

private:

    std::vector<SideBarItem*> side_bar_items_;

    int current_selected_item_ = 0;

};

#endif // SIDEBAR_H
