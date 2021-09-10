#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "waypoint_type.h"

namespace md::domain
{
class Waypoint : public Entity
{
    Q_OBJECT

public:
    explicit Waypoint(const QVariant& id, const QString& name, QObject* parent = nullptr);
};
} // namespace md::domain

#endif // WAYPOINT_H
