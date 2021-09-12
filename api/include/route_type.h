#ifndef ROUTE_TYPE_H
#define ROUTE_TYPE_H

#include "waypoint_type.h"

namespace md::domain
{
class RouteType
{
public:
    RouteType(const QString& name, const QList<WaypointType>& waypointTypes);

    const QString& name() const;
    const QList<WaypointType>& waypointTypes() const;

private:
    const QString m_name;
    const QList<WaypointType> m_waypointTypes;
};
} // namespace md::domain

#endif // ROUTE_TYPE_H
