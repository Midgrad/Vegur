#include "routes_controller.h"

#include <QDebug>

#include "routes_repository_files.h"

namespace
{
constexpr char folder[] = "./routes";
} // namespace

using namespace vegur::domain;
using namespace vegur::endpoint;

RoutesController::RoutesController(QObject* parent) :
    QObject(parent),
    m_repository(new domain::RoutesRepositoryFiles(::folder, this))
{
    connect(m_repository, &domain::IRoutesRepository::routesChanged, this,
            &RoutesController::routesChanged);
}

QJsonArray RoutesController::routes() const
{
    QJsonArray routes;

    for (const QJsonObject& route : m_repository->routes())
    {
        QString name = route.value(rote_params::name).toString();
        if (m_filterString.isEmpty() || name.contains(m_filterString, Qt::CaseInsensitive))
            routes.append(route);
    }
    return routes;
}

void RoutesController::filter(const QString& filterString)
{
    m_filterString = filterString;
    emit routesChanged();
}

void RoutesController::createRoute(const QString& name)
{
    QJsonObject route;
    route.insert(rote_params::name, name);
    // TODO: utils name to path
    // TODO: route types & templates
    m_repository->saveRoute(route);
}

void RoutesController::removeRoute(const QString& routeId)
{
    m_repository->removeRoute(routeId);
}
