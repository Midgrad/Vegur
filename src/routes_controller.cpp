#include "routes_controller.h"

#include <QDebug>

#include "json_repository_files.h"
#include "route_traits.h"

namespace
{
constexpr char routesFolder[] = "./routes";
constexpr char routeTypesFolder[] = "./route_types";
constexpr float altitudeOffset = 50.0;
} // namespace

using namespace vegur::domain;
using namespace kjarni::domain;
using namespace vegur::endpoint;

RoutesController::RoutesController(QObject* parent) :
    QObject(parent),
    m_uow(new JsonRepositoryFiles(::routesFolder), new JsonRepositoryFiles(::routeTypesFolder), this)
{
    m_uow.updateRouteTypes();
    m_uow.updateRoutes();

    connect(&m_uow, &domain::RoutesUow::routesChanged, this, &RoutesController::routesChanged);
    connect(&m_uow, &domain::RoutesUow::routeTypesChanged, this,
            &RoutesController::routeTypesChanged);
}

QJsonArray RoutesController::routes() const
{
    QJsonArray routes;
    for (const QJsonObject& route : m_uow.routes())
    {
        routes.append(route);
    }
    return routes;
}

QJsonArray RoutesController::routeTypes() const
{
    QJsonArray routeTypes;
    for (const QJsonObject& routeType : m_uow.routeTypes())
    {
        routeTypes.append(routeType);
    }
    return routeTypes;
}

QJsonObject RoutesController::centerPosition() const
{
    return m_centerPosition.toJson();
}

void RoutesController::createRoute(const QJsonObject& type)
{
    QVariantMap features;

    features[route_features::centerPosition] = m_centerPosition.offsetted(0, 0, ::altitudeOffset)
                                                   .toJson();

    m_uow.createRoute(type, features);
}

void RoutesController::removeRoute(const QString& routeId)
{
    m_uow.removeRoute(routeId);
}

void RoutesController::renameRoute(const QString& routeId, const QString& name)
{
    m_uow.renameRoute(routeId, name);
}

void RoutesController::setCenterPosition(const QJsonObject& newCenterPosition)
{
    if (m_centerPosition == newCenterPosition)
        return;

    m_centerPosition = newCenterPosition;
    emit centerPositionChanged();
}
