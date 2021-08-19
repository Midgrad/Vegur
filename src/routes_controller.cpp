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
using namespace kjarni::domain;
using namespace vegur::endpoint;

RoutesController::RoutesController(QObject* parent) :
    QObject(parent),
    m_routes(new JsonRepositoryFiles(::routesFolder, this)),
    m_routeTypes(new JsonRepositoryFiles(::routeTypesFolder, this))
{
    connect(m_routes, &IJsonRepository::itemsChanged, this, &RoutesController::routesChanged);
    connect(m_routeTypes, &IJsonRepository::itemsChanged, this,
            &RoutesController::routeTemplatesChanged);
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

QStringList RoutesController::routeTemplates() const
{
    QStringList routeTemplates;
    for (const QJsonObject& routeType : m_routeTypes->values())
    {
        for (const QJsonValue& routeTemplate : routeType.value(rote_params::templates).toArray())
        {
            routeTemplates.append(routeTemplate.toObject().value(json_params::name).toString());
        }
    }
    return routeTemplates;
}

void RoutesController::createRoute(const QString& typeName)
{
    QStringList names;
    for (const QJsonObject& route : m_routes->values())
    {
        names.append(route.value(json_params::name).toString());
    }

    QJsonObject route;
    route.insert(json_params::name, kjarni::utils::nameFromType(typeName, names));
    //route.insert(rote_params::type, type.value(::json_params::id));
    // TODO: route builder

    m_routes->save(route);
}

void RoutesController::removeRoute(const QString& routeId)
{
    m_routes->remove(routeId);
}

void RoutesController::renameRoute(const QString& routeId, const QString& name)
{
    QJsonObject route = m_routes->value(routeId);

    if (route.isEmpty() || route.value(json_params::name).toString() == name)
        return;

    m_routes->remove(routeId);

    route[json_params::name] = name;
    m_routes->save(route);
}
