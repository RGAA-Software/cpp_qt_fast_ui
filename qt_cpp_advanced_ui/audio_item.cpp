#include "audio_item.h"

std::shared_ptr<AudioItem> AudioItem::Make(const QString& icon_url, const QString& name) {
    return std::make_shared<AudioItem>(icon_url, name);
}

AudioItem::AudioItem(const QString& icon_url, const QString& name) {
    this->name_ = name;
}
