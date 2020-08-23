#pragma once

#include <QItemDelegate>

class IngredientsTablePriceDelegate : public QItemDelegate
{
public:
    IngredientsTablePriceDelegate(QObject *parent = nullptr);

private:
    QWidget *createEditor(QWidget *                   parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &         index) const override;

    void paint(QPainter *                  painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &         index) const override;
};
