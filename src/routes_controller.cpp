#include "routes_controller.h"

#include <QDebug>

#include "routes_repository_files.h"

namespace
{
constexpr char folder[] = "./routes";
}

using namespace vegur::domain;
using namespace vegur::endpoint;

RoutesController::RoutesController(QObject* parent) :
    QObject(parent),
    m_repository(new domain::RoutesRepositoryFiles(::folder, this))
{
    connect(m_repository, &domain::IRoutesRepository::routesChanged, this,
            &RoutesController::routesChanged);
}

QStringList RoutesController::routes() const
{
    QStringList list;

    for (const QString& route : m_repository->routes())
    {
        if (m_filterString.isEmpty() || route.contains(m_filterString, Qt::CaseInsensitive))
            list.append(route);
    }
    return list;
}

void RoutesController::filter(const QString& filterString)
{
    m_filterString = filterString;
    emit routesChanged();
}

void RoutesController::createRoute(const QString& name)
{
    // TODO: route types & templates
    m_repository->saveRoute(name, QJsonObject());
}

void RoutesController::removeRoute(const QString& name)
{
    m_repository->removeRoute(name);
}
