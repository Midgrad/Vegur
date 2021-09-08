#ifndef ROUTES_CONTROLLER_H
#define ROUTES_CONTROLLER_H

#include <QJsonObject>
#include <QMap>

#include "entity_model.h"
#include "geodetic.h"
#include "i_missions_service.h"
#include "i_property_tree.h"
#include "routes_uow.h"

namespace md::presentation
{
class RoutesController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QAbstractListModel* missions READ missions CONSTANT)

    Q_PROPERTY(QStringList routes READ routes NOTIFY routesChanged)
    Q_PROPERTY(QStringList routeTypes READ routeTypes NOTIFY routeTypesChanged)

    Q_PROPERTY(QStringList vehicles READ vehicles NOTIFY vehiclesChanged)

    Q_PROPERTY(QJsonObject centerPosition READ centerPosition WRITE setCenterPosition NOTIFY
                   centerPositionChanged)

public:
    explicit RoutesController(QObject* parent = nullptr);

    QAbstractListModel* missions();

    QStringList routes() const;
    QStringList routeTypes() const;
    QStringList vehicles() const;
    QJsonObject centerPosition() const;

    Q_INVOKABLE QJsonObject routeData(const QString& routeId) const;
    Q_INVOKABLE QJsonObject routeTypeData(const QString& typeId) const;

public slots:
    void createRoute(const QString& typeId);
    void removeRoute(const QString& routeId);
    void renameRoute(const QString& routeId, const QString& name);
    void modifyRoute(const QString& routeId, const QString& param, const QVariant& value);

    void assignRoute(const QString& routeId, const QString& vehicleId);

    void setCenterPosition(const QJsonObject& centerPosition);

signals:
    void routeChanged(QString routeId);
    void routesChanged();
    void routeTypesChanged();
    void vehiclesChanged();
    void centerPositionChanged();

    void centerRoute(QString routeId);

private:
    domain::IPropertyTree* const m_pTree;
    domain::IMissionsService* const m_missionsService;
    EntityModel<domain::Mission> m_missionsModel;

    domain::RoutesUow m_uow;
    domain::Geodetic m_centerPosition;
};
} // namespace md::presentation

#endif // ROUTES_CONTROLLER_H
