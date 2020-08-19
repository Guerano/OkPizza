#include "Json.hpp"
#include "model/Ingredient.hpp"

#include <QJsonDocument>

//template<typename T>
QJsonArray Json::from(const std::vector<Ingredient> &v)
{
    QJsonArray res;
    for (auto const &e : v)
        res.push_back(e.toJson());
    //    std::copy(v.begin(), v.end(), std::back_inserter(res));
    return res;
}

//template<typename T, size_t S>
QJsonArray Json::from(const std::array<float, 4> &v)
{
    QJsonArray res;
    std::copy(v.begin(), v.end(), std::back_inserter(res));
    return res;
}

QByteArray Json::toQByteArray(const QJsonObject &json)
{
    return QJsonDocument(json).toJson();
}

QByteArray Json::toQByteArray(const QJsonArray &json)
{
    return QJsonDocument(json).toJson();
}

template<>
QJsonObject Json::fromFile(QFile &file)
{
    if (file.size() == 0)
        return {};

    auto const bytes = file.readAll();

    QJsonParseError error;
    auto const      doc = QJsonDocument::fromJson(bytes, &error);

    if (error.error)
        throw error.errorString();

    return doc.object();
}

template<>
QJsonArray Json::fromFile(QFile &file)
{
    if (file.size() == 0)
        return {};

    auto const bytes = file.readAll();

    QJsonParseError error;
    auto const      doc = QJsonDocument::fromJson(bytes, &error);

    if (error.error)
        throw error.errorString();

    return doc.array();
}