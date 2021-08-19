#ifndef ROUTES_CONTROLLER_H
#define ROUTES_CONTROLLER_H

#include <QJsonArray>
#include <QMap>

#include "routes_uow.h"

namespace vegur::endpoint
{
class RoutesController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QJsonArray routes READ routes NOTIFY routesChanged)
    Q_PROPERTY(QJsonArray routeTypes READ routeTypes NOTIFY routeTypesChanged)

public:
    explicit RoutesController(QObject* parent = nullptr);

    QJsonArray routes() const;
    QJsonArray routeTypes() const;

public slots:
    void createRoute(const QJsonObject& type);
    void removeRoute(const QString& routeId);
    void renameRoute(const QString& routeId, const QString& name);

signals:
    void routesChanged();
    void routeTypesChanged();

private:
    domain::RoutesUow m_uow;
};
} // namespace vegur::endpoint

#endif // ROUTES_CONTROLLER_H
