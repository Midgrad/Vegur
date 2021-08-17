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
    return m_repository->routes();
}

void RoutesController::createRoute(const QString& name)
{
    // TODO: route types & templates
    m_repository->saveRoute(name, QJsonObject());
}
