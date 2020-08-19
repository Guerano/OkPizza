#include "Ingredient.hpp"

Ingredient::Ingredient(const QString &name, float price) noexcept
    : _name(name)
    , _price(price)
{}

Ingredient::Ingredient(const QJsonObject &json)
{
    if (!json.contains(Fields::name))
        throw QString("Missing field 'name' while deserializing an ingredient");
    else
        _name = json[Fields::name].toString();

    if (!json.contains(Fields::price))
        throw QString("Missing field 'price' while deserializing an ingredient");
    else
        _price = json[Fields::price].toDouble();
}

QJsonObject Ingredient::toJson() const
{
    return {{Fields::name, _name}, {Fields::price, _price}};
}

QString Ingredient::name() const
{
    return _name;
}

void Ingredient::setName(const QString &name)
{
    _name = name;
}

float Ingredient::price() const
{
    return _price;
}

void Ingredient::setPrice(float price)
{
    _price = price;
}
