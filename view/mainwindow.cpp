#include "mainwindow.hpp"
#include "model/database/FileDatabase.hpp"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
try : QMainWindow(parent),
      ui(new Ui::MainWindow),
      _db(new FileDatabase(PROJECT_PATH "/Database", "ingredients.json", "pizzas.json"))
{
    ui->setupUi(this);
    QObject::connect(_db, &FileDatabase::ingredientsChanged, this, &MainWindow::fillIngredients);
    QObject::connect(_db, &FileDatabase::pizzasChanged, this, &MainWindow::fillPizzas);
}
catch (QString &error)
{
    qDebug() << error;
}

MainWindow::~MainWindow()
{
    delete _db;
    delete ui;
}

void MainWindow::fillIngredients()
{
    auto comboBoxIngredients = ui->orders->findChild<QComboBox *>("comboBoxIngredients");
    if (!comboBoxIngredients)
        throw "Could not find comboBoxIngredients in tab 'order'";

    QStringList ingredientsName;
    for (auto const &ingredient : _db->ingredients())
        ingredientsName << ingredient.name();

    comboBoxIngredients->clear();
    comboBoxIngredients->addItems(ingredientsName);
}

void MainWindow::fillPizzas()
{
    auto comboBoxPizzas = ui->orders->findChild<QComboBox *>("comboBoxPizzas");
    if (!comboBoxPizzas)
        throw "Could not find comboBoxPizzas in tab 'order'";

    QStringList pizzasName;
    for (auto const &pizza : _db->pizzas())
        pizzasName << pizza.name();

    comboBoxPizzas->clear();
    comboBoxPizzas->addItems(pizzasName);
}
