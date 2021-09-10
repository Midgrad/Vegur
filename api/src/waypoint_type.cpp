#include "waypoint_type.h"

using namespace md::domain;

WaypointType::WaypointType(const QVariant& id, const QString& name, QObject* parent) :
    Entity(id, name, parent)
{
}
