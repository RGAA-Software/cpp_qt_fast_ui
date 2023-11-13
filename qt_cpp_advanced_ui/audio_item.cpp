#include "audio_item.h"

std::shared_ptr<AudioItem> AudioItem::Make(const QString& icon_url, const QString& name) {
    return std::make_shared<AudioItem>(icon_url, name);
}

AudioItem::AudioItem(const QString& icon_url, const QString& name) {
    this->name_ = name;

    QImage image;
    image.load(icon_url);
    pixmap_ = QPixmap::fromImage(image);
    pixmap_ = pixmap_.scaled(98, 98, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    mask_ = QBitmap(pixmap_.width(), pixmap_.height());

}
