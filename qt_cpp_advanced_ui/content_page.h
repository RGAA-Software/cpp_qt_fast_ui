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

private:

    int item_count_ = 0;
    int item_size_ = 0;
    int padding_top_ = 0;

    int padding_size_ = 5;

    std::vector<std::shared_ptr<AudioItem>> audio_items_;

};

#endif // CONTENTPAGE_H
