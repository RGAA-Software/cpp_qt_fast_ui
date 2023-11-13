#ifndef CONTENTPAGE_H
#define CONTENTPAGE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class AudioItem;

class ContentPage : public QWidget
{
    Q_OBJECT
public:
    explicit ContentPage(int item_count, int item_size, int padding_top, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void UpdateAudioItems(const std::vector<std::shared_ptr<AudioItem>>& items);
    void SetMarginTop(int mt);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


private:

    int item_count_ = 0;
    int item_size_ = 0;
    int padding_top_ = 0;
    int margin_top_ = 0;
    int padding_size_ = 5;

    QPoint current_mouse_pos_{-1,-1};
    std::shared_ptr<AudioItem> current_item_ = nullptr;

    std::vector<std::shared_ptr<AudioItem>> audio_items_;

};

#endif // CONTENTPAGE_H
