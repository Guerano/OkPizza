#pragma once

#include <vector>

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>

class Ingredient;

namespace Json
{
//template<typename T>
QJsonArray from(std::vector<Ingredient> const& v);

//template<typename T, size_t S>
QJsonArray from(const std::array<float, 4>& v);

QByteArray toQByteArray(QJsonObject const& json);
QByteArray toQByteArray(QJsonArray const& json);

template<typename T>
T fromFile(QFile& file) = delete;

template<>
QJsonObject fromFile(QFile& file);

template<>
QJsonArray fromFile(QFile& file);
} // namespace Json
