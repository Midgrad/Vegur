#include "mission_type.h"

using namespace md::domain;

MissionType::MissionType(const QVariant& id, const QString& name,
                         const QList<RouteType*>& routeTypes, QObject* parent) :
    Entity(id, name, parent),
    m_routeTypes(routeTypes)
{
    for (RouteType* routeType : m_routeTypes)
    {
        routeType->setParent(this);
    }
}

const QList<RouteType*>& MissionType::routeTypes() const
{
    return m_routeTypes;
}
