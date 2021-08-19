#ifndef ROUTE_CREATOR_H
#define ROUTE_CREATOR_H

#include <QJsonObject>
#include <QStringList>

namespace vegur::domain
{
class RouteCreator
{
public:
    RouteCreator(const QJsonObject& type, const QStringList& bannedNames);

    QJsonObject create();

private:
    QJsonObject const m_type;
    QStringList const m_bannedNames;
};
} // namespace vegur::domain

#endif // ROUTE_CREATOR_H
