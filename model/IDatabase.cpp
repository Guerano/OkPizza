#include "IDatabase.hpp"

std::optional<const Ingredient> IDatabase::hasIngredient(const QString &name) const
{
    auto const it = std::find_if(_ingredients.begin(), _ingredients.end(), [&name](auto const &e) {
        return e.name() == name;
    });

    if (it == _ingredients.end())
        return {};
    else
        return *it;
}

std::optional<Ingredient> IDatabase::hasIngredient(const QString &name)
{
    auto const it = std::find_if(_ingredients.begin(), _ingredients.end(), [&name](auto const &e) {
        return e.name() == name;
    });

    if (it == _ingredients.end())
        return {};
    else
        return *it;
}

std::optional<const Ingredient> IDatabase::hasIngredient(const Ingredient &ingredient) const
{
    auto it = std::find_if(_ingredients.begin(), _ingredients.end(), [&ingredient](auto const &e) {
        return e.name() == ingredient.name();
    });

    if (it == _ingredients.end())
        return {};
    else
        return *it;
}

std::optional<Ingredient> IDatabase::hasIngredient(const Ingredient &ingredient)
{
    auto it = std::find_if(_ingredients.begin(), _ingredients.end(), [&ingredient](auto const &e) {
        return e.name() == ingredient.name();
    });

    if (it == _ingredients.end())
        return {};
    else
        return *it;
}

std::optional<const Pizza> IDatabase::hasPizza(const QString &name) const
{
    auto it = std::find_if(_pizzas.begin(), _pizzas.end(), [&name](auto const &e) {
        return e.name() == name;
    });

    if (it == _pizzas.end())
        return {};
    else
        return *it;
}

std::optional<Pizza> IDatabase::hasPizza(const QString &name)
{
    auto it = std::find_if(_pizzas.begin(), _pizzas.end(), [&name](auto const &e) {
        return e.name() == name;
    });

    if (it == _pizzas.end())
        return {};
    else
        return *it;
}

std::optional<const Pizza> IDatabase::hasPizza(const Pizza &pizza) const
{
    auto it = std::find_if(_pizzas.begin(), _pizzas.end(), [&pizza](auto const &e) {
        return e.name() == pizza.name();
    });

    if (it == _pizzas.end())
        return {};
    else
        return std::optional<Pizza>(*it); // FIXME: this shit should not work
}

std::optional<Pizza> IDatabase::hasPizza(const Pizza &pizza)
{
    auto it = std::find_if(_pizzas.begin(), _pizzas.end(), [&pizza](auto const &e) {
        return e.name() == pizza.name();
    });

    if (it == _pizzas.end())
        return {};
    else
        return std::optional<const Pizza>(*it); // FIXME: this shit should not work
}

void IDatabase::purge()
{
    removeAllIngredients();
    removeAllPizzas();
}

void IDatabase::removeAllIngredients()
{
    _ingredients.clear();

    emit ingredientsChanged();
}

void IDatabase::removeAllPizzas()
{
    _pizzas.clear();

    emit pizzasChanged();
}
