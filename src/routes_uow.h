#ifndef ROUTES_UOW_H
#define ROUTES_UOW_H

#include <QMap>

#include "i_json_repository.h"

namespace vegur::domain
{
class RoutesUow : public QObject
{
    Q_OBJECT
public:
    RoutesUow(kjarni::domain::IJsonRepository* routesRepository,
              kjarni::domain::IJsonRepository* routeTypesRepository, QObject* parent = nullptr);

    QList<QJsonObject> routes() const;
    QList<QJsonObject> routeTypes() const;

    QJsonObject route(const QString& routeId) const;
    QJsonObject routeType(const QString& routeId) const;

public slots:
    void updateRoutes();
    void updateRouteTypes();

    void saveRoute(const QString& routeId, const QJsonObject& routeData);
    void removeRoute(const QString& routeId);
    void createRoute(const QString& templateId);
    void renameRoute(const QString& routeId, const QString& name);

signals:
    void routesChanged();
    void routeTypesChanged();

private:
    QStringList routeNames() const;

    kjarni::domain::IJsonRepository* const m_routesRepository;
    kjarni::domain::IJsonRepository* const m_routeTypesRepository;

    QMap<QString, QJsonObject> m_routes;
    QMap<QString, QJsonObject> m_routeTypes;
};
} // namespace vegur::domain

#endif // ROUTES_UOW_H
