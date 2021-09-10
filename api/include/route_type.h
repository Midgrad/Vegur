#ifndef ROUTE_TYPE_H
#define ROUTE_TYPE_H

#include "waypoint_type.h"

namespace md::domain
{
class RouteType : public Entity
{
    Q_OBJECT

public:
    RouteType(const QVariant& id, const QString& name, const QList<WaypointType*>& waypointTypes,
              QObject* parent = nullptr);

    const QList<WaypointType*>& waypointTypes() const;

private:
    const QList<WaypointType*> m_waypointTypes;
};
} // namespace md::domain

#endif // ROUTE_TYPE_H
