#ifndef ROUTES_CONTROLLER_H
#define ROUTES_CONTROLLER_H

#include <QJsonArray>
#include <QMap>

#include "geodetic.h"
#include "routes_uow.h"

namespace vegur::endpoint
{
class RoutesController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QJsonArray routes READ routes NOTIFY routesChanged)
    Q_PROPERTY(QJsonArray routeTypes READ routeTypes NOTIFY routeTypesChanged)
    Q_PROPERTY(QJsonObject centerPosition READ centerPosition WRITE setCenterPosition NOTIFY
                   centerPositionChanged)

public:
    explicit RoutesController(QObject* parent = nullptr);

    QJsonArray routes() const;
    QJsonArray routeTypes() const;
    QJsonObject centerPosition() const;

public slots:
    void createRoute(const QJsonObject& type);
    void removeRoute(const QString& routeId);
    void renameRoute(const QString& routeId, const QString& name);
    void setCenterPosition(const QJsonObject& centerPosition);

signals:
    void routesChanged();
    void routeTypesChanged();
    void centerPositionChanged();

private:
    domain::RoutesUow m_uow;
    jord::domain::Geodetic m_centerPosition;
};
} // namespace vegur::endpoint

#endif // ROUTES_CONTROLLER_H
