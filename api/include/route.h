#ifndef ROUTE_H
#define ROUTE_H

#include "waypoint.h"

namespace md::domain
{
class Route : public Entity
{
    Q_OBJECT

public:
    Route(const QString& name, QObject* parent = nullptr);

    int count() const;
    const QList<Waypoint*>& waypoints() const;
    Waypoint* waypoint(int index) const;

public slots:
    void addWaypoint(Waypoint* waypoint);
    void removeWaypoint(Waypoint* waypoint);

signals:
    void waypointAdded(Waypoint* waypoint);
    void waypointRemoved(Waypoint* waypoint);

private:
    const QList<WaypointType> m_waypoinsTypes;
    QList<Waypoint*> m_waypoins;
};
} // namespace md::domain

#endif // ROUTE_H
