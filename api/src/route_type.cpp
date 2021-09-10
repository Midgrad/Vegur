#include "mission_type.h"

using namespace md::domain;

RouteType::RouteType(const QVariant& id, const QString& name,
                     const QList<WaypointType*>& waypointTypes, QObject* parent) :
    Entity(id, name, parent),
    m_waypointTypes(waypointTypes)
{
}

const QList<WaypointType*>& RouteType::waypointTypes() const
{
    return m_waypointTypes;
}
