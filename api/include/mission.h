#ifndef MISSION_H
#define MISSION_H

#include "route.h"

namespace md::domain
{
class Mission : public Entity
{
    Q_OBJECT

    Q_PROPERTY(QString vehicle READ vehicle WRITE setVehicle NOTIFY vehicleChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit Mission(const QString& name = QString(), QObject* parent = nullptr);

    QString vehicle() const;
    QString name() const;
    Route* route() const;

public slots:
    void setVehicle(const QString& vehicle);
    void setName(const QString& name);
    void setRoute(Route* route);

signals:
    void vehicleChanged(QString vehicle);
    void nameChanged(QString name);
    void routeChanged(Route* route);

private:
    QString m_vehicle;
    QString m_name;
    Route* m_route = nullptr;
};
} // namespace md::domain

#endif // MISSION_H
