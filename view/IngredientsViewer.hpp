#pragma once

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
    void on_ingredientsTableWidget_itemChanged(QTableWidgetItem *item);

    void onIngredientsTableRightClick(const QPoint &pos);

private:
    Ui::IngredientsViewer *ui;
};

