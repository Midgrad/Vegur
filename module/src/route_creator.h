#ifndef ROUTE_CREATOR_H
#define ROUTE_CREATOR_H

#include <QJsonObject>
#include <QVariantMap>

namespace md::domain
{
class RouteCreator
{
public:
    RouteCreator(const QJsonObject& type, const QVariantMap& features);

    QJsonObject create();

private:
    QJsonObject const m_type;
    QVariantMap const m_features;
};
} // namespace vegur::domain

#endif // ROUTE_CREATOR_H
