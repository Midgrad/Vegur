#ifndef WAYPOINT_TYPE_H
#define WAYPOINT_TYPE_H

#include <QList>
#include <QString>

namespace md::domain
{
class WaypointType
{
public:
    WaypointType(const QString& name);

    virtual const QString& name() const;

private:
    const QString m_name;
};
} // namespace md::domain

#endif // WAYPOINT_TYPE_H
