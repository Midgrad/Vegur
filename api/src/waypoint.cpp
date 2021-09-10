#include "waypoint.h"

using namespace md::domain;

Waypoint::Waypoint(const QVariant& id, const QString& name, QObject* parent) :
    Entity(id, name, parent)
{
}
