#include "routes_controller.h"

#include <QDebug>

#include "json_repository_files.h"
#include "route_traits.h"

namespace
{
constexpr char routesFolder[] = "./routes";
constexpr char routeTypesFolder[] = "./route_types";
} // namespace

using namespace md::domain;
using namespace md::presentation;

RoutesController::RoutesController(QObject* parent) :
    QObject(parent),
    m_uow(new data_source::JsonRepositoryFiles(::routesFolder),
          new data_source::JsonRepositoryFiles(::routeTypesFolder), this)
{
    m_uow.updateRouteTypes();
    m_uow.updateRoutes();

    connect(&m_uow, &RoutesUow::routesChanged, this, &RoutesController::routesChanged);
    connect(&m_uow, &RoutesUow::routeTypesChanged, this, &RoutesController::routeTypesChanged);
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

    features[route_features::centerPosition] = m_centerPosition.toJson();

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

void RoutesController::modifyRoute(const QString& routeId, const QString& param,
                                   const QVariant& value)
{
    QJsonObject route = m_uow.route(routeId);
    if (route.isEmpty())
        return;

    route[param] = QJsonValue::fromVariant(value);

    m_uow.saveRoute(route);
    emit routesChanged();
}

void RoutesController::setCenterPosition(const QJsonObject& centerPosition)
{
    m_centerPosition = centerPosition;
    emit centerPositionChanged();
}
