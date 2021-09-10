#include "route.h"

using namespace md::domain;

Route::Route(const QVariant& id, const QString& name, QObject* parent) : Entity(id, name, parent)
{
}

const QList<Waypoint*>& Route::waypoins() const
{
    return m_waypoins;
}

void Route::addWaypoint(Waypoint* waypoint)
{
    if (m_waypoins.contains(waypoint))
        return;

    if (!waypoint->parent())
        waypoint->setParent(this);

    m_waypoins.append(waypoint);
    emit waypointAdded(waypoint);
}

void Route::removeWaypoint(Waypoint* waypoint)
{
    if (!m_waypoins.contains(waypoint))
        return;

    if (waypoint->parent() == this)
        waypoint->setParent(nullptr);

    m_waypoins.removeOne(waypoint);
    emit waypointRemoved(waypoint);
}
