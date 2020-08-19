#pragma once

#include "Ingredient.hpp"
#include "utils/IJsonSerializable.hpp"

#include <array>

class IDatabase;

class Pizza : public IJsonSerializable
{
public:
    using Prices = std::array<float, 4>;

    struct Fields
    {
        constexpr static auto const cost        = "cost";
        constexpr static auto const ingredients = "ingredients";
        constexpr static auto const name        = "name";
        constexpr static auto const prices      = "prices";
        constexpr static auto const size        = "size";

        constexpr static auto const smallSize  = "SMALL";
        constexpr static auto const mediumSize = "MEDIUM";
        constexpr static auto const largeSize  = "LARGE";
        constexpr static auto const xlargeSize = "XLARGE";
    };

    enum Size
    {
        SMALL,
        MEDIUM,
        LARGE,
        XLARGE
    };

public:
    Pizza(QString const&                 name,
          Size                           size,
          Prices                         prices,
          std::vector<Ingredient> const& ingredients) noexcept;
    Pizza(QJsonObject const& json, IDatabase const& database);

public:
    QJsonObject toJson() const override;

    QString name() const;
    void    setName(QString const& name);

    Size size() const;
    void setSize(Size size);

    std::vector<Ingredient> ingredients() const;
    void                    setIngredients(std::vector<Ingredient> const& ingredients);
    void                   addIngredient(Ingredient const& ingredient);
    void                   removeIngredient(Ingredient const& ingredient);
    void                   removeAllIngredients();

    float  cost() const;           // Real price due to ingredients
    float  price(Size size) const; // Sold price proportionally to its size
    Prices prices() const;
    void   setPrice(Prices prices);
    void   setPrice(Size size, float price);

public:
    static QString sizeToString(Size size);
    static Size    sizeFromString(QString const& size);

private:
    QString                _name;
    Size                   _size;
    std::vector<Ingredient> _ingredients;
    float                  _cost; // Minimum cost due to ingredients' cost
    Prices                 _prices;
};
