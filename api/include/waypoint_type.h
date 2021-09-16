#ifndef WAYPOINT_TYPE_H
#define WAYPOINT_TYPE_H

#include <QVariant>
#include <QVector>

namespace md::domain
{
class Parameter
{
public:
    enum Type
    {
        Bool,
        Int,
        Real,
        Coordinate
    };
    Parameter(const QString& name, Type type = Real, const QVariant& defaultValue = 0,
              const QVariant& minValue = -qInf(), const QVariant& maxValue = qInf(),
              const QVariant& step = 1);
    Parameter(const Parameter& other);

    bool isNull() const;

    const QString name;
    const Type type;
    const QVariant defaultValue;
    const QVariant minValue;
    const QVariant maxValue;
    const QVariant step;
};

class WaypointType
{
public:
    WaypointType(const QString& name, const QVector<Parameter>& parameters);

    Parameter parameter(const QString& name) const;

    const QString name;
    const QVector<Parameter> parameters;
};
} // namespace md::domain

#endif // WAYPOINT_TYPE_H
