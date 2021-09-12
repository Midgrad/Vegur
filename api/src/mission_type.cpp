#include "mission_type.h"

using namespace md::domain;

MissionType::MissionType(const QString& name, const QList<RouteType>& routeTypes) :
    m_name(name),
    m_routeTypes(routeTypes)
{
}

const QString& MissionType::name() const
{
    return m_name;
}

const QList<RouteType>& MissionType::routeTypes() const
{
    return m_routeTypes;
}
