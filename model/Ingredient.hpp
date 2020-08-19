#pragma once

#include "utils/IJsonSerializable.hpp"

#include <QString>

class FileDatabase;

class Ingredient : public IJsonSerializable
{
public:
    struct Fields
    {
        constexpr static auto const name  = "name";
        constexpr static auto const price = "price";
    };

public:
    Ingredient(QString const &name, float price) noexcept;
    Ingredient(QJsonObject const &json);

public:
    QJsonObject toJson() const override;

    QString name() const;
    void    setName(QString const &name);

    float price() const;
    void  setPrice(float price);

private:
    QString _name;
    float   _price;
};