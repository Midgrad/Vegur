#ifndef WAYPOINT_TYPE_H
#define WAYPOINT_TYPE_H

#include "entity.h"

namespace md::domain
{
class WaypointParameter
{
public:
    QString name;
    QString type;
    QString unit;
    QVariant min;
    QVariant max;
    QVariant step;
};

class WaypointType : public Entity
{
    Q_OBJECT

public:
    explicit WaypointType(const QVariant& id, const QString& name, QObject* parent = nullptr);
};
} // namespace md::domain

#endif // WAYPOINT_TYPE_H
