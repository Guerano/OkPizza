#pragma once

#include "model/IDatabase.hpp"
#include "model/database/FileDatabase.hpp"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void fillIngredients();
    void fillPizzas();

private:
    Ui::MainWindow *ui;

    FileDatabase *_db;
};