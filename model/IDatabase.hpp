#pragma once

#include "Ingredient.hpp"
#include "Pizza.hpp"

#include <optional>
#include <vector>

#include <QObject>

class IDatabase : public QObject
{
public:
    using Ingredients = std::vector<Ingredient>;
    using Pizzas      = std::vector<Pizza>;

    struct Fields
    {
        constexpr static auto const ingredients = "ingredients";
        constexpr static auto const pizzas      = "pizzas";
    };

public:
    virtual ~IDatabase() = default;

public:    
    virtual Ingredients ingredients() const = 0;
    virtual Pizzas      pizzas() const      = 0;

    virtual void addIngredients(Ingredient const &ingredient) = 0;
    virtual void addPizzas(Pizza const &pizza)                = 0;

    std::optional<const Ingredient> hasIngredient(QString const &name) const;
    std::optional<Ingredient>       hasIngredient(QString const &name);
    std::optional<const Ingredient> hasIngredient(Ingredient const &ingredient) const;
    std::optional<Ingredient>       hasIngredient(Ingredient const &ingredient);

    std::optional<const Pizza> hasPizza(QString const &name) const;
    std::optional<Pizza>       hasPizza(QString const &name);
    std::optional<const Pizza> hasPizza(Pizza const &pizza) const;
    std::optional<Pizza>       hasPizza(Pizza const &pizza);

signals:
    virtual void ingredientsChanged() const = 0;
    virtual void pizzasChanged() const      = 0;

protected:
    virtual void load()            = 0;
    virtual void loadIngredients() = 0;
    virtual void loadPizzas()      = 0;

    virtual void save() const            = 0; // write to supposed file
    virtual void saveIngredients() const = 0;
    virtual void savePizzas() const      = 0;

    virtual void backup() const            = 0; // write to backup file
    virtual void backupIngredients() const = 0;
    virtual void backupPizzas() const      = 0;

    void purge(); // remove database data from memory, but not disk
    void removeAllIngredients();
    void removeAllPizzas();

protected:
    Ingredients _ingredients;
    Pizzas      _pizzas;
};

Q_DECLARE_INTERFACE(IDatabase, "OkPizza.IDatabase");