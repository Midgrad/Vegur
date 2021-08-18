#ifndef I_ROUTES_REPOSITORY_H
#define I_ROUTES_REPOSITORY_H

#include <QJsonObject>
#include <QObject>

#include "route_traits.h"

namespace vegur::domain
{
// TODO: Generic IJsonRepository
class IRoutesRepository : public QObject
{
    Q_OBJECT

public:
    IRoutesRepository(QObject* parent = nullptr) : QObject(parent)
    {
    }

    virtual QStringList ids() const = 0;
    virtual QList<QJsonObject> routes() const = 0;
    virtual QJsonObject route(const QString& routeId) const = 0;

    virtual void saveRoute(const QJsonObject& routeData) = 0;
    virtual void removeRoute(const QString& routeId) = 0;

signals:
    void routeAdded(QString routeId);
    void routeChanged(QString routeId);
    void routeRemoved(QString routeId);
    void routesChanged();
};
} // namespace vegur::domain

#endif // I_ROUTES_REPOSITORY_H
