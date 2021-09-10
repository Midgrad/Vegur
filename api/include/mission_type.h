#ifndef MISSION_TYPE_H
#define MISSION_TYPE_H

#include "route_type.h"

namespace md::domain
{
class MissionType : public Entity
{
    Q_OBJECT

public:
    MissionType(const QVariant& id, const QString& name, const QList<RouteType*>& routeTypes,
                QObject* parent = nullptr);

    const QList<RouteType*>& routeTypes() const;

private:
    const QList<RouteType*> m_routeTypes;
};
} // namespace md::domain

#endif // MISSION_TYPE_H
