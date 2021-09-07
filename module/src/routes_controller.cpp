#include "routes_controller.h"

#include <QDebug>

#include "json_repository_files.h"
#include "locator.h"
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
    m_pTree(md::app::Locator::get<IPropertyTree>()),
    m_uow(new data_source::JsonRepositoryFiles(::routesFolder),
          new data_source::JsonRepositoryFiles(::routeTypesFolder), this)
{
    Q_ASSERT(m_pTree);

    connect(m_pTree, &IPropertyTree::rootNodesChanged, this, &RoutesController::vehiclesChanged);

    m_uow.updateRouteTypes();
    m_uow.updateRoutes();

    connect(&m_uow, &RoutesUow::routeChanged, this, &RoutesController::routeChanged);
    connect(&m_uow, &RoutesUow::routesChanged, this, &RoutesController::routesChanged);
    connect(&m_uow, &RoutesUow::routeTypesChanged, this, &RoutesController::routeTypesChanged);
}

QStringList RoutesController::routes() const
{
    return m_uow.routeIds();
}

QStringList RoutesController::routeTypes() const
{
    return m_uow.routeTypeIds();
}

QStringList RoutesController::vehicles() const
{
    // TODO: vehicles only
    QStringList result = m_pTree->rootNodes();
    result.prepend(QString());
    return result;
}

QJsonObject RoutesController::centerPosition() const
{
    return m_centerPosition.toJson();
}

QJsonObject RoutesController::routeData(const QString& routeId) const
{
    return m_uow.route(routeId);
}

QJsonObject RoutesController::routeTypeData(const QString& typeId) const
{
    return m_uow.routeType(typeId);
}

void RoutesController::createRoute(const QString& typeId)
{
    QVariantMap features;

    features[route_features::centerPosition] = m_centerPosition.toJson();

    m_uow.createRoute(typeId, features);
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

    m_uow.saveRoute(routeId, route);
}

void RoutesController::assignRoute(const QString& routeId, const QString& vehicleId)
{
    this->modifyRoute(routeId, "vehicle", vehicleId);
}

void RoutesController::setCenterPosition(const QJsonObject& centerPosition)
{
    m_centerPosition = centerPosition;
    emit centerPositionChanged();
}
