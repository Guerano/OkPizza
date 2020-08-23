#include "mainwindow.hpp"
#include "model/database/FileDatabase.hpp"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QStyleFactory>
#include <QTouchEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _settings("settings.ini", QSettings::Format::IniFormat, nullptr)
{
    ui->setupUi(this);

    QApplication::setStyle(_settings.value("theme", QStyleFactory::keys().first()).toString());

    auto const themes = QStyleFactory::keys();
    for (auto theme : themes)
    {
        auto action = ui->menuThemes->addAction(theme);
        connect(action, &QAction::triggered, [this, theme]() {
            QApplication::setStyle(theme);
            _settings.setValue("theme", theme);
        });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}