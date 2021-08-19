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
    Q_PROPERTY(QStringList routeTemplates READ routeTemplates NOTIFY routeTemplatesChanged)

public:
    explicit RoutesController(QObject* parent = nullptr);

    QJsonArray routes() const;
    QStringList routeTemplates() const;

public slots:
    void createRoute(const QString& templateId);
    void removeRoute(const QString& routeId);
    void renameRoute(const QString& routeId, const QString& name);

signals:
    void routesChanged();
    void routeTemplatesChanged();

private:
    domain::RoutesUow m_uow;
};
} // namespace vegur::endpoint

#endif // ROUTES_CONTROLLER_H
