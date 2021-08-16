#ifndef VEHICLES_CONTROLLER_H
#define VEHICLES_CONTROLLER_H

#include <QJsonArray>
#include <QObject>

namespace draken::endpoint
{
class RoutesController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QJsonArray routes READ routes NOTIFY routesChanged)

public:
    explicit RoutesController(QObject* parent = nullptr);

    QJsonArray routes() const;

signals:
    void routesChanged();

private:
    QJsonArray m_routes;
};
} // namespace draken::endpoint

#endif // VEHICLES_CONTROLLER_H
