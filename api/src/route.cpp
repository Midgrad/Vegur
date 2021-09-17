#include "route.h"

#include <QJsonArray>

using namespace md::domain;

Route::Route(const QString& name, QObject* parent) : Entity(name, parent)
{
}

QJsonObject Route::toJson() const
{
    QJsonObject json = Entity::toJson();

    QJsonArray waypoints;
    for (Waypoint* waypoint : m_waypoins)
    {
        waypoints.append(waypoint->toJson());
    }

    json.insert(params::waypoints, waypoints);

    return json;
}

void Route::fromJson(const QJsonObject& json)
{
    Entity::fromJson(json);
}

int Route::count() const
{
    return m_waypoins.count();
}

const QList<Waypoint*>& Route::waypoints() const
{
    return m_waypoins;
}

Waypoint* Route::waypoint(int index) const
{
    return m_waypoins.value(index, nullptr);
}

void Route::addWaypoint(Waypoint* waypoint)
{
    if (m_waypoins.contains(waypoint))
        return;

    if (waypoint->thread() != this->thread())
        waypoint->moveToThread(this->thread());

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
