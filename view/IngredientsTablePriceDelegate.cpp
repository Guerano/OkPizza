#include "IngredientsTablePriceDelegate.hpp"

#include <QDebug>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QPainter>

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
    item->setSuffix(" €");
    return item;
}

void IngredientsTablePriceDelegate::paint(QPainter *                  painter,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &         index) const
{
    painter->save();

    auto value = index.data().toString() + " €";

    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    painter->drawText(option.rect, Qt::AlignVCenter | Qt::AlignLeft, value);

    painter->restore();
}