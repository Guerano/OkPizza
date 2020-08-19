#include "IngredientsViewer.hpp"
#include "ui_IngredientsViewer.h"

#include "IngredientsTablePriceDelegate.hpp"

#include <QCheckBox>
#include <QDebug>
#include <QItemDelegate>
#include <QMenu>

IngredientsViewer::IngredientsViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IngredientsViewer)
{
    ui->setupUi(this);
    ui->ingredientsTableWidget->resizeColumnsToContents();

    auto priceDelegate = new IngredientsTablePriceDelegate();
    ui->ingredientsTableWidget->setItemDelegateForColumn(1, priceDelegate);

    connect(ui->ingredientsTableWidget,
            &QTableWidget::customContextMenuRequested,
            this,
            &IngredientsViewer::onIngredientsTableRightClick);
}

IngredientsViewer::~IngredientsViewer()
{
    delete ui;
}

void IngredientsViewer::on_ingredientsTableWidget_itemChanged(QTableWidgetItem *)
{
    ui->ingredientsTableWidget->resizeColumnsToContents();
}

void IngredientsViewer::onIngredientsTableRightClick(const QPoint &pos)
{
    QTableWidgetItem *item = ui->ingredientsTableWidget->itemAt(pos);
    if (item)
    {
        auto menu = new QMenu(ui->ingredientsTableWidget);
        menu->addAction("Supprimer");
        menu->exec(QCursor::pos());
    }
}