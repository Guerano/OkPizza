#pragma once

#include "../model/database/SqliteDatabase.hpp"

#include <QTableWidgetItem>
#include <QWidget>

namespace Ui {
class IngredientsViewer;
}

class IngredientsViewer : public QWidget
{
    Q_OBJECT

public:
    explicit IngredientsViewer(QWidget *parent = nullptr);
    ~IngredientsViewer();

private slots:
    void onIngredientsTableRightClick(const QPoint &pos);

    void on_newIngredientAddButton_clicked();

private:
    Ui::IngredientsViewer *ui;

    SqliteDatabase _db;
};

