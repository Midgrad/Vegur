#ifndef ROUTES_UOW_H
#define ROUTES_UOW_H

#include <QVariantMap>

#include "i_json_repository.h"

namespace md::domain
{
class RoutesUow : public QObject
{
    Q_OBJECT
public:
    RoutesUow(data_source::IJsonRepository* routesRepository,
              data_source::IJsonRepository* routeTypesRepository, QObject* parent = nullptr);

    QStringList routeIds() const;
    QList<QJsonObject> routes() const;
    QStringList routeTypeIds() const;
    QList<QJsonObject> routeTypes() const;

    QJsonObject route(const QString& routeId) const;
    QJsonObject routeType(const QString& typeId) const;

public slots:
    void updateRoutes();
    void updateRouteTypes();

    void saveRoute(const QString& routeId, const QJsonObject& routeData);
    void removeRoute(const QString& routeId);
    void createRoute(const QString& typeId, const QVariantMap& features = QVariantMap());
    void renameRoute(const QString& routeId, const QString& name);

signals:
    void routeChanged(QString routeId);
    void routesChanged();
    void routeTypesChanged();

private:
    QStringList routeNames() const;

    data_source::IJsonRepository* const m_routesRepository;
    data_source::IJsonRepository* const m_routeTypesRepository;

    QMap<QString, QJsonObject> m_routes;
    QMap<QString, QJsonObject> m_routeTypes;
};
} // namespace md::domain

#endif // ROUTES_UOW_H