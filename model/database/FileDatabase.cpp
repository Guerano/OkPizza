#include "FileDatabase.hpp"
#include "utils/Json.hpp"

#include <QDebug>
#include <QObject>

FileDatabase::FileDatabase(QString const &databaseDirectory,
                           QString const &ingrededientsFile,
                           QString const &pizzasFile)
    : _databasePath(databaseDirectory)
    , _ingredientsPath(databaseDirectory + "/" + ingrededientsFile)
    , _pizzasPath(databaseDirectory + "/" + pizzasFile)
    , _databaseWatcher({_databasePath}, nullptr)
    , _ingredientsWatcher({_ingredientsPath}, nullptr)
    , _pizzasWatcher({_pizzasPath}, nullptr)
{
    QObject::connect(&_databaseWatcher,
                     &QFileSystemWatcher::directoryChanged,
                     this,
                     &FileDatabase::onDatabaseDirectoryChanged);

    QObject::connect(&_ingredientsWatcher,
                     &QFileSystemWatcher::fileChanged,
                     this,
                     &FileDatabase::onIngredientsFileChanged);

    QObject::connect(&_pizzasWatcher,
                     &QFileSystemWatcher::fileChanged,
                     this,
                     &FileDatabase::onPizzasFileChanged);

    qInfo() << "Keeping track of " + databaseDirectory;
    qInfo() << "Keeping track of " + databaseDirectory + '/' + ingrededientsFile;
    qInfo() << "Keeping track of " + databaseDirectory + '/' + pizzasFile;
}

IDatabase::Ingredients FileDatabase::ingredients() const
{
    return _ingredients;
}

IDatabase::Pizzas FileDatabase::pizzas() const
{
    return _pizzas;
}

void FileDatabase::addIngredients(Ingredient const &ingredient)
{
    _ingredients.push_back(ingredient);
}

void FileDatabase::addPizzas(Pizza const &pizza)
{
    _pizzas.push_back(pizza);
}

void FileDatabase::onDatabaseDirectoryChanged(const QString &)
{ // TODO
}

void FileDatabase::onIngredientsFileChanged(const QString &)
{
    backupIngredients();
    loadIngredients();
}

void FileDatabase::onPizzasFileChanged(const QString &)
{
    backupPizzas();
    loadPizzas();
}

void FileDatabase::load()
{
    loadIngredients();
    loadPizzas();
}

void FileDatabase::loadIngredients()
{
    if (QFile ingredientsFile(_ingredientsPath); !ingredientsFile.open(QIODevice::ReadOnly))
        throw "Could not open ingredients file for loading at location: " + _ingredientsPath;
    else
    {
        _ingredients.clear();
        auto const ingredientsArray = Json::fromFile<QJsonArray>(ingredientsFile);
        for (auto const &ingredient : ingredientsArray)
            _ingredients.emplace_back(ingredient.toObject());
    }

    qInfo() << QString::number(_ingredients.size())
                   + " ingredients loaded from: " + _ingredientsPath;

    emit ingredientsChanged();
}

void FileDatabase::loadPizzas()
{
    if (QFile pizzasFile(_pizzasPath); !pizzasFile.open(QIODevice::ReadOnly))
        throw "Could not open pizzas file for loading at location: " + _pizzasPath;
    else
    {
        _pizzas.clear();
        auto const pizzasArray = Json::fromFile<QJsonArray>(pizzasFile);
        for (auto const &pizza : pizzasArray)
            _pizzas.emplace_back(pizza.toObject(), *this);
    }

    qInfo() << QString::number(_pizzas.size()) + " pizzas loaded from: " + _pizzasPath;

    emit pizzasChanged();
}

void FileDatabase::save() const
{
    saveIngredients();
    savePizzas();
}

void FileDatabase::saveIngredients() const
{
    if (QFile ingredientsFile(_ingredientsPath); !ingredientsFile.open(QIODevice::WriteOnly))
        throw "Could not open ingredients file for saving at location: " + _ingredientsPath;
    else
    {
        QJsonArray ingredientsArray;
        for (auto const &ingredient : _ingredients)
            ingredientsArray.push_back(ingredient.toJson());
        ingredientsFile.write(Json::toQByteArray(ingredientsArray));
    }

    qInfo() << "Ingredients saved to: " + _ingredientsPath;
}

void FileDatabase::savePizzas() const
{
    if (QFile pizzasFile(_pizzasPath); !pizzasFile.open(QIODevice::WriteOnly))
        throw "Could not open pizzas file for saving at location: " + _pizzasPath;
    else
    {
        QJsonArray pizzasArray;
        for (auto const &pizza : _pizzas)
            pizzasArray.push_back(pizza.toJson());
        pizzasFile.write(Json::toQByteArray(pizzasArray));
    }

    qInfo() << "Pizzas saved to: " + _pizzasPath;
}

void FileDatabase::backup() const
{
    backupIngredients();
    backupPizzas();
}

void FileDatabase::backupIngredients() const
{
    auto const path = _ingredientsPath + ".bkp";
    if (QFile ingredientsFile(path); !ingredientsFile.open(QIODevice::WriteOnly))
        throw "Could not open ingredients file for backing up at location: " + path;
    else
    {
        QJsonArray ingredientsArray;
        for (auto const &ingredient : _ingredients)
            ingredientsArray.push_back(ingredient.toJson());
        ingredientsFile.write(Json::toQByteArray(ingredientsArray));
    }

    qInfo() << "Ingredients backed up to: " + path;
}

void FileDatabase::backupPizzas() const
{
    auto const path = _pizzasPath + ".bkp";
    if (QFile pizzasFile(path); !pizzasFile.open(QIODevice::WriteOnly))
        throw "Could not open pizzas file for backing up at location: " + path;
    else
    {
        QJsonArray pizzasArray;
        for (auto const &pizza : _pizzas)
            pizzasArray.push_back(pizza.toJson());
        pizzasFile.write(Json::toQByteArray(pizzasArray));
    }

    qInfo() << "Pizzas backed up to: " + path;
}
