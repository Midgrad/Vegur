#ifndef MISSION_H
#define MISSION_H

#include "route.h"

namespace md::domain
{
class Mission : public Entity
{
    Q_OBJECT

    Q_PROPERTY(QString vehicle READ vehicle WRITE setVehicle NOTIFY vehicleChanged)

public:
    explicit Mission(const QVariant& id, const QString& name, QObject* parent = nullptr);

    QString vehicle() const;
    Route* route() const;

public slots:
    void setVehicle(const QString& vehicle);
    void setRoute(Route* route);

signals:
    void vehicleChanged(QString vehicle);
    void routeChanged(Route* route);

private:
    QString m_vehicle;
    Route* m_route = nullptr;
};
} // namespace md::domain

#endif // MISSION_H
