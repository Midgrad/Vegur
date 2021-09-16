#include "waypoint_type.h"

using namespace md::domain;

Parameter::Parameter(const QString& name, Type type, const QVariant& defaultValue,
                     const QVariant& minValue, const QVariant& maxValue, const QVariant& step) :
    name(name),
    type(type),
    defaultValue(defaultValue),
    minValue(minValue),
    maxValue(maxValue),
    step(step)
{
}

Parameter::Parameter(const Parameter& other) :
    Parameter(other.name, other.type, other.defaultValue, other.minValue, other.maxValue, other.step)
{
}

WaypointType::WaypointType(const QString& name, const QVector<Parameter>& parameters) :
    name(name),
    parameters(parameters)
{
}
