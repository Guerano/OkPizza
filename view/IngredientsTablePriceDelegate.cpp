#include "IngredientsTablePriceDelegate.hpp"

#include <QDebug>
#include <QDoubleSpinBox>
#include <QLineEdit>

IngredientsTablePriceDelegate::IngredientsTablePriceDelegate(QObject *parent)
    : QItemDelegate(parent)
{}

QWidget *IngredientsTablePriceDelegate::createEditor(QWidget *parent,
                                                     const QStyleOptionViewItem &,
                                                     const QModelIndex &) const
{
    auto item = new QDoubleSpinBox(parent);
    item->setRange(0, 1000);
    item->setButtonSymbols(QAbstractSpinBox::NoButtons);
    return item;
}