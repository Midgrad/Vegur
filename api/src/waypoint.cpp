#include "waypoint.h"

using namespace md::domain;

Waypoint::Waypoint(const WaypointType* type, QObject* parent) :
    Entity(type->name, parent),
    m_type(type)
{
    this->syncParameters();
}

const WaypointType* Waypoint::type() const
{
    return m_type;
}

void Waypoint::setType(const WaypointType* type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged();

    this->syncParameters();
}

void Waypoint::syncParameters()
{
    QStringList unneededParameters = this->parameters().keys();
    for (const Parameter& parameter : m_type->parameters)
    {
        // If parameter exist - remove it from unneededParameters
        if (!unneededParameters.removeOne(parameter.name))
        {
            // Or add it with default value
            this->setParameter(parameter.name, parameter.defaultValue);
        }
    }
    this->removeParameters(unneededParameters);
}

void Waypoint::resetParameter(const QString& key)
{
    Parameter parameter = m_type->parameter(key);
    if (parameter.isNull())
        return;

    this->setParameter(key, parameter.defaultValue);
}
