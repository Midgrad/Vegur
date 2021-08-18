#include "routes_controller.h"

#include <QDebug>

#include "routes_repository_files.h"
#include "utils.h"

namespace
{
constexpr char routesFolder[] = "./routes";
constexpr char routeTypesFolder[] = "./route_types";
} // namespace

using namespace vegur::domain;
using namespace vegur::endpoint;

RoutesController::RoutesController(QObject* parent) :
    QObject(parent),
    m_routes(new domain::RoutesRepositoryFiles(::routesFolder, this)),
    m_routeTypes(new domain::RoutesRepositoryFiles(::routeTypesFolder, this))
{
    connect(m_routes, &domain::IRoutesRepository::routesChanged, this,
            &RoutesController::routesChanged);
    connect(m_routeTypes, &domain::IRoutesRepository::routesChanged, this,
            &RoutesController::routeTypesChanged);
}

QJsonArray RoutesController::routes() const
{
    QJsonArray routes;

    for (const QJsonObject& route : m_routes->routes())
    {
        routes.append(route);
    }
    return routes;
}

QJsonArray RoutesController::routeTypes() const
{
    QJsonArray routeTypes;

    for (const QJsonObject& route : m_routeTypes->routes())
    {
        routeTypes.append(route);
    }
    return routeTypes;
}

void RoutesController::createRoute(const QJsonObject& type)
{
    QString typeName = type.value(rote_params::name).toString();
    if (typeName.isEmpty())
        return;

    QStringList names;
    for (const QJsonObject& route : m_routes->routes())
    {
        names.append(route.value(rote_params::name).toString());
    }

    QJsonObject route;
    route.insert(rote_params::name, kjarni::utils::nameFromType(typeName, names));
    route.insert(rote_params::type, type.value(rote_params::id));
    // TODO: route builder

    m_routes->saveRoute(route);
}

void RoutesController::removeRoute(const QString& routeId)
{
    m_routes->removeRoute(routeId);
}
