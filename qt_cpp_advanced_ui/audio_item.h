#ifndef AUDIOITEM_H
#define AUDIOITEM_H

#include <QString>

#include <memory>

class AudioItem
{
public:

    static std::shared_ptr<AudioItem> Make(const QString& icon_url, const QString& name);

    AudioItem(const QString& icon_url, const QString& name);

public:

    QString name_;

};

#endif // AUDIOITEM_H
