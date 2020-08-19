#pragma once

#include "../IDatabase.hpp"

#include <QDir>
#include <QFile>
#include <QFileSystemWatcher>
#include <QString>

class FileDatabase : public IDatabase
{
    Q_OBJECT
    Q_INTERFACES(IDatabase)

public:
    FileDatabase(QString const &databaseDirectory,
                 QString const &ingrededientsFile,
                 QString const &pizzasFile);
    ~FileDatabase() override = default;

    Ingredients ingredients() const override;
    Pizzas      pizzas() const override;

    void addIngredients(Ingredient const &ingredient) override;
    void addPizzas(Pizza const &pizza) override;

signals:
    void ingredientsChanged() const override;
    void pizzasChanged() const override;

private slots:
    void onDatabaseDirectoryChanged(QString const &path);
    void onIngredientsFileChanged(QString const &path);
    void onPizzasFileChanged(QString const &path);

private:
    void load() override;
    void loadIngredients() override;
    void loadPizzas() override;

    void save() const override;
    void saveIngredients() const override;
    void savePizzas() const override;

    void backup() const override;
    void backupIngredients() const override;
    void backupPizzas() const override;

private:
    QString const _databasePath;
    QString const _ingredientsPath;
    QString const _pizzasPath;

    QFileSystemWatcher _databaseWatcher;
    QFileSystemWatcher _ingredientsWatcher;
    QFileSystemWatcher _pizzasWatcher;
};
