#pragma once

#define CONSTANT constexpr auto const

namespace Sqlite::Query
{
CONSTANT createIngredientsTable = "CREATE TABLE IF NOT EXISTS ingredients "
                                  "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                  "name VARCHAR(20) NOT NULL UNIQUE, "
                                  "price REAL NOT NULL, "
                                  "CHECK(name <> ''))";

CONSTANT createPizzasTable = "CREATE TABLE IF NOT EXISTS pizzas "
                             "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                             "name VARCHAR(20) NOT NULL UNIQUE, "
                             "price REAL NOT NULL)";

CONSTANT dropTable = "DROP TABLE IF EXISTS :table";
} // namespace Sqlite::Query