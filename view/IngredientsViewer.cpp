#include "IngredientsViewer.hpp"
#include "ui_IngredientsViewer.h"

#include "IngredientsTablePriceDelegate.hpp"

#include <QCheckBox>
#include <QDebug>
#include <QItemDelegate>
#include <QMenu>
#include <QMessageBox>
#include <QSqlError>

IngredientsViewer::IngredientsViewer(QWidget *parent)
try : QWidget(parent), ui(new Ui::IngredientsViewer), _db(PROJECT_PATH "/Database/db.sqlite")
{
    ui->setupUi(this);
    ui->ingredientsTableView->setModel(&_db.ingredientsModel());
    ui->ingredientsTableView->setColumnHidden(0, true);
    ui->ingredientsTableView->resizeColumnsToContents();

    auto priceDelegate = new IngredientsTablePriceDelegate();
    ui->ingredientsTableView->setItemDelegateForColumn(2, priceDelegate);

    connect(ui->ingredientsTableView,
            &QTableView::customContextMenuRequested,
            this,
            &IngredientsViewer::onIngredientsTableRightClick);

    layout()->setContentsMargins(2, 2, 2, 2);
}
catch (QString const &error)
{
    qWarning() << "Something went wrong in IngredientsViewer: " << error;
}

IngredientsViewer::~IngredientsViewer()
{
    delete ui;
}

void IngredientsViewer::onIngredientsTableRightClick(const QPoint &pos)
{
    auto item         = ui->ingredientsTableView->indexAt(pos);
    auto menu         = new QMenu(ui->ingredientsTableView);
    auto deleteAction = menu->addAction("Supprimer");

    connect(deleteAction, &QAction::triggered, [this, item]() {
        //        _db.ingredientsModel().removeRow(item.row());
        _db.removeIngredient(item.row());
    });

    menu->exec(QCursor::pos());
}
void IngredientsViewer::on_newIngredientAddButton_clicked()
{
    auto name  = ui->newIngredientNameLineEdit->text();
    auto price = ui->newIngredientPriceDoubleSpinBox->value();

    if (!_db.addIngredient(name.trimmed(), price))
    {
        auto errorMsg = name.isEmpty() ? tr("Le nom de l'ingredient ne doit pas être vide.")
                                       : tr("Impossible de rajouter cet ingrédient.");

        QMessageBox::warning(this, tr("Ajout d'un nouvel ingrédient"), errorMsg);
        if (name.isEmpty())
            ui->newIngredientNameLineEdit->setFocus();
    }
    else
    {
        ui->newIngredientNameLineEdit->clear();
        ui->newIngredientNameLineEdit->setFocus();
    }
}