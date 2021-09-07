#ifndef ROUTE_H
#define ROUTE_H

#include "waypoint.h"

namespace md::domain
{
class Route : public Entity
{
    Q_OBJECT

public:
    explicit Route(QObject* parent = nullptr);

    const QList<Waypoint*>& waypoins() const;

public slots:
    void addWaypoint(Waypoint* waypoint);
    void removeWaypoint(Waypoint* waypoint);

signals:
    void waypointAdded(Waypoint* waypoint);
    void waypointRemoved(Waypoint* waypoint);

private:
    QList<Waypoint*> m_waypoins;
};
} // namespace md::domain

#endif // ROUTE_H
