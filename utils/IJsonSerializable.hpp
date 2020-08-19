#pragma once

#include <QJsonObject>

struct IJsonSerializable
{
    virtual ~IJsonSerializable() = default;

    virtual QJsonObject toJson() const = 0;
};
