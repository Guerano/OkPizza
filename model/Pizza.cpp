#include "Pizza.hpp"
#include "IDatabase.hpp"
#include "utils/Json.hpp"

#include <QJsonArray>

Pizza::Pizza(QString const &               name,
             Size                          size,
             Prices                        prices,
             IDatabase::Ingredients const &ingredients) noexcept
    : _name(name)
    , _size(size)
    , _prices(prices)
{
    for (auto const &ingredient : ingredients)
    {
        _ingredients.push_back(ingredient);
        _cost += ingredient.price();
    }
}

Pizza::Pizza(QJsonObject const &json, IDatabase const &database)
{
    if (!json.contains(Fields::name))
        throw "Missing field 'name' when deserializing Pizza";
    if (!json.contains(Fields::size))
        throw "Missing field 'size' when deserializing Pizza";
    if (!json.contains(Fields::prices))
        throw "Missing field 'prices' when deserializing Pizza";
    if (!json.contains(Fields::ingredients))
        throw "Missing field 'ingredients' when deserializing Pizza";

    _name = json[Fields::name].toString();
    _size = sizeFromString(json[Fields::size].toString());

    auto const prices = json[Fields::prices].toArray();
    for (int i = 0; i < static_cast<int>(_prices.size()); ++i)
    {
        if (i > prices.size() - 1)
            _prices[i] = 0;
        else
            _prices[i] = prices[i].toDouble();
    }

    auto const jsonIngredients = json[Fields::ingredients].toArray();

    for (auto const &jsonIngredientValue : jsonIngredients)
    {
        auto jsonIngredient = jsonIngredientValue.toObject();

        if (!jsonIngredient.contains(Ingredient::Fields::name))
            throw "Missing ingredients' names while deserializing pizza " + _name;
        auto const jsonIngredientName = jsonIngredient[Ingredient::Fields::name].toString();

        if (auto ingredient = database.hasIngredient(jsonIngredientName))
        {
            _cost += ingredient->price();
            _ingredients.push_back(*ingredient);
        }
        else
        {
            throw "The ingredient '" + jsonIngredient[Ingredient::Fields::name].toString()
                + "' required for the pizza '" + _name + "' is not in the database";
        }
    }
}

QJsonObject Pizza::toJson() const
{
    return {
        {Fields::name, _name},
        {Fields::size, _size},
        {Fields::prices, Json::from(_prices)},
        {Fields::ingredients, Json::from(_ingredients)},
    };
}

QString Pizza::name() const
{
    return _name;
}

void Pizza::setName(const QString &name)
{
    _name = name;
}

Pizza::Size Pizza::size() const
{
    return _size;
}

void Pizza::setSize(Size size)
{
    _size = size;
}

IDatabase::Ingredients Pizza::ingredients() const
{
    return _ingredients;
}

void Pizza::setIngredients(const IDatabase::Ingredients &ingredients)
{
    _ingredients = ingredients;
}

void Pizza::addIngredient(const Ingredient &ingredient)
{
    _ingredients.push_back(ingredient);
}

void Pizza::removeIngredient(const Ingredient &ingredient)
{
    auto it = std::remove_if(_ingredients.begin(), _ingredients.end(), [ingredient](auto const &e) {
        return e.name() == ingredient.name();
    });
    _ingredients.erase(it);
}

void Pizza::removeAllIngredients()
{
    _ingredients.clear();
}

float Pizza::cost() const
{
    return _cost;
}

float Pizza::price(Size size) const
{
    if (size < 0 || size > _prices.size())
    {
        throw "Could not get the price of the pizza '" + _name
            + "' for the size: " + sizeToString(size);
    }
    return _prices[size];
}

Pizza::Prices Pizza::prices() const
{
    return _prices;
}

void Pizza::setPrice(Pizza::Prices prices)
{
    _prices = prices;
}

void Pizza::setPrice(Pizza::Size size, float price)
{
    if (size < 0 || size > _prices.size())
    {
        throw "Could not set the price of the pizza '" + _name
            + "' for the size: " + sizeToString(size);
    }
    _prices[size] = price;
}

QString Pizza::sizeToString(Pizza::Size size)
{
    switch (size)
    {
        case SMALL:
            return Fields::smallSize;
        case MEDIUM:
            return Fields::mediumSize;
        case LARGE:
            return Fields::largeSize;
        case XLARGE:
            return Fields::xlargeSize;
        default:
            throw "Cannot convert pizza size to string, unknown value";
    }
}

Pizza::Size Pizza::sizeFromString(const QString &size)
{
    if (size == Fields::smallSize)
        return SMALL;
    else if (size == Fields::mediumSize)
        return MEDIUM;
    else if (size == Fields::largeSize)
        return LARGE;
    else if (size == Fields::xlargeSize)
        return XLARGE;
    else
        throw "Unknown size for pizza: " + size;
}
