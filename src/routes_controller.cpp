#include "routes_controller.h"

#include <QDebug>

#include "json_repository_files.h"
#include "route_traits.h"
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
    m_routes(new kjarni::domain::JsonRepositoryFiles(::routesFolder, this)),
    m_routeTypes(new kjarni::domain::JsonRepositoryFiles(::routeTypesFolder, this))
{
    connect(m_routes, &kjarni::domain::IJsonRepository::itemsChanged, this,
            &RoutesController::routesChanged);
    connect(m_routeTypes, &kjarni::domain::IJsonRepository::itemsChanged, this,
            &RoutesController::routeTypesChanged);
}

QJsonArray RoutesController::routes() const
{
    QJsonArray routes;

    for (const QJsonObject& route : m_routes->values())
    {
        routes.append(route);
    }
    return routes;
}

QJsonArray RoutesController::routeTypes() const
{
    QJsonArray routeTypes;

    for (const QJsonObject& route : m_routeTypes->values())
    {
        routeTypes.append(route);
    }
    return routeTypes;
}

void RoutesController::createRoute(const QJsonObject& type)
{
    QString typeName = type.value(kjarni::domain::json_params::name).toString();
    if (typeName.isEmpty())
        return;

    QStringList names;
    for (const QJsonObject& route : m_routes->values())
    {
        names.append(route.value(kjarni::domain::json_params::name).toString());
    }

    QJsonObject route;
    route.insert(kjarni::domain::json_params::name, kjarni::utils::nameFromType(typeName, names));
    route.insert(rote_params::type, type.value(kjarni::domain::json_params::id));
    // TODO: route builder

    m_routes->save(route);
}

void RoutesController::removeRoute(const QString& routeId)
{
    m_routes->remove(routeId);
}
