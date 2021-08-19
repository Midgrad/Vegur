#ifndef ROUTES_CONTROLLER_H
#define ROUTES_CONTROLLER_H

#include <QJsonArray>

#include "i_json_repository.h"

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
    void createRoute(const QString& typeName);
    void removeRoute(const QString& routeId);
    void renameRoute(const QString& routeId, const QString& name);

signals:
    void routesChanged();
    void routeTemplatesChanged();

private:
    kjarni::domain::IJsonRepository* const m_routes;
    kjarni::domain::IJsonRepository* const m_routeTypes;
};
} // namespace vegur::endpoint

#endif // ROUTES_CONTROLLER_H
