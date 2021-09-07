#include "routes_uow.h"

#include <QDebug>
#include <QJsonArray>

#include "route_creator.h"
#include "route_traits.h"

using namespace md::domain;

RoutesUow::RoutesUow(data_source::IJsonRepository* routesRepository,
                     data_source::IJsonRepository* routeTypesRepository, QObject* parent) :
    QObject(parent),
    m_routesRepository(routesRepository),
    m_routeTypesRepository(routeTypesRepository)
{
    m_routesRepository->setParent(this);
    m_routeTypesRepository->setParent(this);

    connect(m_routesRepository, &data_source::IJsonRepository::itemsChanged, this,
            &RoutesUow::updateRoutes);
    connect(m_routeTypesRepository, &data_source::IJsonRepository::itemsChanged, this,
            &RoutesUow::updateRouteTypes);
}

QStringList RoutesUow::routeIds() const
{
    return m_routes.keys();
}

QList<QJsonObject> RoutesUow::routes() const
{
    return m_routes.values();
}

QStringList RoutesUow::routeTypeIds() const
{
    return m_routeTypes.keys();
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
    bool changed = false;
    QStringList oldIds = this->routeIds();

    for (const QString& routeId : m_routesRepository->selectIds())
    {
        QJsonObject newRoute = m_routesRepository->read(routeId);
        // Update existing routes
        if (oldIds.contains(routeId))
        {
            if (m_routes.value(routeId) != newRoute)
            {
                m_routes[routeId] = newRoute;
                emit routeChanged(routeId);
            }
            // Don't distub unchanged routes
            oldIds.removeOne(routeId);
        }
        // Insert new route
        else
        {
            m_routes.insert(routeId, newRoute);
            changed = true;
        }
    }

    // Remove rotten routes
    for (const QString& routeId : oldIds)
    {
        m_routes.remove(routeId);
        changed = true;
    }

    if (changed)
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

void RoutesUow::saveRoute(const QString& routeId, const QJsonObject& routeData)
{
    if (m_routes.value(routeId) == routeData)
        return;

    m_routesRepository->save(routeData);
    m_routes[routeId] = routeData;
    emit routeChanged(routeId);
}

void RoutesUow::removeRoute(const QString& routeId)
{
    m_routesRepository->remove(routeId);
}

void RoutesUow::createRoute(const QString& typeId, const QVariantMap& features)
{
    QJsonObject type = this->routeType(typeId);
    if (type.isEmpty())
        return;

    QVariantMap modified(features);
    modified[route_features::bannedNames] = this->routeNames();

    RouteCreator creator(type, modified);
    QJsonObject route = creator.create();
    if (route.isEmpty())
        return;

    m_routesRepository->save(route);
}

void RoutesUow::renameRoute(const QString& routeId, const QString& name)
{
    QJsonObject route = m_routes.value(routeId);

    if (route.isEmpty() || route.value(params::name).toString() == name ||
        this->routeNames().contains(name))
        return;

    this->removeRoute(routeId);

    route[params::name] = name;
    this->saveRoute(routeId, route);
}

QStringList RoutesUow::routeNames() const
{
    QStringList names;
    for (const QJsonObject& route : m_routes.values())
    {
        names.append(route.value(params::name).toString());
    }
    return names;
}
