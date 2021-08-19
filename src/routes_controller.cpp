#include "routes_controller.h"

#include <QDebug>

#include "json_repository_files.h"
#include "route_traits.h"

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
    m_uow(new JsonRepositoryFiles(::routesFolder), new JsonRepositoryFiles(::routeTypesFolder), this)
{
    m_uow.updateRouteTypes();
    m_uow.updateRoutes();

    connect(&m_uow, &domain::RoutesUow::routesChanged, this, &RoutesController::routesChanged);
    connect(&m_uow, &domain::RoutesUow::routeTypesChanged, this,
            &RoutesController::routeTemplatesChanged);
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

QStringList RoutesController::routeTemplates() const
{
    QStringList routeTemplates;
    for (const QJsonObject& routeType : m_uow.routeTypes())
    {
        for (const QJsonValue& routeTemplate : routeType.value(rote_params::templates).toArray())
        {
            routeTemplates.append(routeTemplate.toObject().value(json_params::name).toString());
        }
    }
    return routeTemplates;
}

void RoutesController::createRoute(const QString& templateId)
{
    m_uow.createRoute(templateId);
}

void RoutesController::removeRoute(const QString& routeId)
{
    m_uow.removeRoute(routeId);
}

void RoutesController::renameRoute(const QString& routeId, const QString& name)
{
    m_uow.renameRoute(routeId, name);
}
