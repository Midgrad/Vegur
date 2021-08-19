#include "routes_uow.h"

#include <QJsonArray>

#include "route_creator.h"
#include "route_traits.h"

using namespace kjarni::domain;
using namespace vegur::domain;

RoutesUow::RoutesUow(IJsonRepository* routesRepository, IJsonRepository* routeTypesRepository,
                     QObject* parent) :
    QObject(parent),
    m_routesRepository(routesRepository),
    m_routeTypesRepository(routeTypesRepository)
{
    m_routesRepository->setParent(this);
    m_routeTypesRepository->setParent(this);

    connect(m_routesRepository, &IJsonRepository::itemsChanged, this, &RoutesUow::updateRoutes);
    connect(m_routeTypesRepository, &IJsonRepository::itemsChanged, this,
            &RoutesUow::updateRouteTypes);
}

QList<QJsonObject> RoutesUow::routes() const
{
    return m_routes.values();
}

QList<QJsonObject> RoutesUow::routeTypes() const
{
    return m_routeTypes.values();
}

QJsonObject RoutesUow::route(const QString& routeId) const
{
    return m_routes.value(routeId);
}

QJsonObject RoutesUow::routeType(const QString& typeId) const
{
    return m_routeTypes.value(typeId);
}

void RoutesUow::updateRoutes()
{
    for (const QString& routeId : m_routesRepository->selectIds())
    {
        m_routes[routeId] = m_routesRepository->read(routeId);
    }
    emit routesChanged();
}

void RoutesUow::updateRouteTypes()
{
    for (const QString& typeId : m_routeTypesRepository->selectIds())
    {
        QJsonObject routeType = m_routeTypesRepository->read(typeId);
        m_routeTypes[typeId] = routeType;
    }
    emit routeTypesChanged();
}

void RoutesUow::saveRoute(const QJsonObject& routeData)
{
    QJsonObject data = routeData;
    m_routesRepository->save(data);
    QString routeId = data.value(kjarni_params::id).toString();
    if (routeId.isNull())
        return;

    m_routes[routeId] = data;
}

void RoutesUow::removeRoute(const QString& routeId)
{
    m_routes.remove(routeId);
    m_routesRepository->remove(routeId);
}

void RoutesUow::createRoute(const QJsonObject& type)
{
    RouteCreator creator(type, this->routeNames());
    QJsonObject route = creator.create();
    if (route.isEmpty())
        return;

    m_routesRepository->save(route);
}

void RoutesUow::renameRoute(const QString& routeId, const QString& name)
{
    QJsonObject route = m_routes.value(routeId);

    if (route.isEmpty() || route.value(kjarni_params::name).toString() == name ||
        this->routeNames().contains(name))
        return;

    this->removeRoute(routeId);

    route[kjarni_params::name] = name;
    this->saveRoute(route);
}

QStringList RoutesUow::routeNames() const
{
    QStringList names;
    for (const QJsonObject& route : m_routes.values())
    {
        names.append(route.value(kjarni_params::name).toString());
    }
    return names;
}
