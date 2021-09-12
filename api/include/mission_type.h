#ifndef MISSION_TYPE_H
#define MISSION_TYPE_H

#include "route_type.h"

namespace md::domain
{
class MissionType
{
public:
    MissionType(const QString& name, const QList<RouteType>& routeTypes);

    const QString& name() const;
    const QList<RouteType>& routeTypes() const;

private:
    const QString m_name;
    const QList<RouteType> m_routeTypes;
};
} // namespace md::domain

#endif // MISSION_TYPE_H
