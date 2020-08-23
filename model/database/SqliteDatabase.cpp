#include "SqliteDatabase.hpp"
#include "SqlQueries.hpp"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

SqliteDatabase::SqliteDatabase(QString const& dbPath)
    : _db(QSqlDatabase::addDatabase("QSQLITE"))
    , _ingredientsModel(nullptr, _db)
    , _pizzasModel(nullptr, _db)
{
    if (!setupDb(dbPath))
        throw _db.lastError().text();

    _ingredientsModel.setTable(Fields::ingredients);
    _ingredientsModel.setEditStrategy(QSqlTableModel::OnFieldChange);
    _ingredientsModel.select();

    _pizzasModel.setTable(Fields::ingredients);
    _pizzasModel.setEditStrategy(QSqlTableModel::OnFieldChange);
    _pizzasModel.select();
}

QSqlTableModel& SqliteDatabase::ingredientsModel()
{
    return _ingredientsModel;
}

QSqlTableModel& SqliteDatabase::pizzasModel()
{
    return _pizzasModel;
}

bool SqliteDatabase::addIngredient(const QString& name, double price)
{
    QSqlRecord newIngredient = _ingredientsModel.record();
    newIngredient.setValue("name", name);
    newIngredient.setValue("price", price);

    if (!_ingredientsModel.insertRecord(_ingredientsModel.rowCount(), newIngredient))
    {
        qWarning() << "Could not add ingredient '" << name
                   << "': " << _ingredientsModel.database().lastError().text();
        return false;
    }

    _ingredientsModel.select();
    return true;
}

bool SqliteDatabase::removeIngredient(int row)
{
    _ingredientsModel.removeRow(row);
    _ingredientsModel.select();
    return true;
}

bool SqliteDatabase::addPizza()
{
    return false;
}

bool SqliteDatabase::removePizza(int row)
{
    Q_UNUSED(row);
    return false;
}

QString SqliteDatabase::lastError() const
{
    return _db.lastError().text();
}

bool SqliteDatabase::setupDb(QString const& dbPath)
{
    _db.setDatabaseName(dbPath);

    if (!_db.open())
        return false;

    auto tables = _db.tables();
    for (auto const& table : tables)
        qDebug() << "sql table: " << table;

    if (!tables.contains(Fields::ingredients) || !tables.contains(Fields::pizzas))
    {
        qInfo() << "The database is not setup yet, creating tables...";
        if (!createIngredientsTable())
            return false;
        if (!createPizzasTable())
            return false;
    }

    return true;
}

bool SqliteDatabase::dropTable(const QString& tableName)
{
    QSqlQuery query;
    query.prepare(Sqlite::Query::dropTable);
    query.bindValue(":table", tableName);

    if (!query.exec())
    {
        qWarning() << "Could not drop table " << tableName << ": " << _db.lastError().text();
        return false;
    }

    return true;
}

bool SqliteDatabase::createIngredientsTable()
{
    QSqlQuery query(_db);
    if (!query.exec(Sqlite::Query::createIngredientsTable))
    {
        qWarning() << "Could not create ingredients table: " << _db.lastError().text();
        return false;
    }

    return true;
}

bool SqliteDatabase::createPizzasTable()
{
    QSqlQuery query(_db);
    if (!query.exec(Sqlite::Query::createPizzasTable))
    {
        qWarning() << "Could not create pizzas table: " << _db.lastError().text();
        return false;
    }

    return true;
}
