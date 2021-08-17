#ifndef I_ROUTES_REPOSITORY_H
#define I_ROUTES_REPOSITORY_H

#include <QJsonObject>
#include <QObject>

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

    virtual QStringList routes() const = 0;
    virtual QJsonObject route(const QString& route) const = 0;

    virtual void saveRoute(const QString& route, const QJsonObject& data) = 0;
    virtual void removeRoute(const QString& route) = 0;

signals:
    void routesChanged();
};
} // namespace vegur::domain

#endif // I_ROUTES_REPOSITORY_H
