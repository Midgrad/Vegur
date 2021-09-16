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

bool Parameter::isNull() const
{
    return name.isNull(); // This is enough
}

namespace md::domain
{
bool operator==(const Parameter& left, const Parameter& right)
{
    return left.name == right.name;
}
} // namespace md::domain

WaypointType::WaypointType(const QString& name, const QVector<Parameter>& parameters) :
    name(name),
    parameters(parameters)
{
}

Parameter WaypointType::parameter(const QString& name) const
{
    auto result = std::find_if(parameters.begin(), parameters.end(),
                               [name](const Parameter& parameter) {
                                   return parameter.name == name;
                               });
    if (result != std::end(parameters))
        return *result;

    return Parameter(QString());
}
