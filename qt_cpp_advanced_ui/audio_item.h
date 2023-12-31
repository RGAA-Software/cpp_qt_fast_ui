#ifndef AUDIOITEM_H
#define AUDIOITEM_H

#include <QRect>
#include <QString>
#include <QPixmap>
#include <QBitmap>

#include <memory>

class AudioItem
{
public:

    static std::shared_ptr<AudioItem> Make(const QString& icon_url, const QString& name);

    AudioItem(const QString& icon_url, const QString& name);

public:

    QString name_;
    QRect draw_rect_;
    QPixmap pixmap_;
    QBitmap mask_;

};

#endif // AUDIOITEM_H
