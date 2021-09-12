#include "waypoint_type.h"

using namespace md::domain;

WaypointType::WaypointType(const QString& name) : m_name(name)
{
}

const QString& WaypointType::name() const
{
    return m_name;
}
