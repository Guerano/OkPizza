#pragma once

//#include "../IDatabase.hpp"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QString>

class SqliteDatabase
{
public:
    struct Fields
    {
        constexpr static auto const ingredients = "ingredients";
        constexpr static auto const pizzas      = "pizzas";
    };

public:
    SqliteDatabase(QString const& dbPath);

    QSqlTableModel& ingredientsModel();
    QSqlTableModel& pizzasModel();

public:
    bool addIngredient(QString const& name, double price);
    bool removeIngredient(int row);

    bool addPizza();
    bool removePizza(int row);

    QString lastError() const;

private:
    bool setupDb(QString const& dbPath);
    bool dropTable(QString const& tableName);
    bool createIngredientsTable();
    bool createPizzasTable();

private:
    QSqlDatabase   _db;
    QSqlTableModel _ingredientsModel;
    QSqlTableModel _pizzasModel;
};
