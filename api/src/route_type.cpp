#include "mission_type.h"

using namespace md::domain;

RouteType::RouteType(const QString& name, const QList<WaypointType>& waypointTypes) :
    m_name(name),
    m_waypointTypes(waypointTypes)
{
}

const QString& RouteType::name() const
{
    return m_name;
}

const QList<WaypointType>& RouteType::waypointTypes() const
{
    return m_waypointTypes;
}
