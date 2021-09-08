#include "mission.h"

using namespace md::domain;

Mission::Mission(const QString& name, QObject* parent) : Entity(parent), m_name(name)
{
}

QString Mission::vehicle() const
{
    return m_vehicle;
}

QString Mission::name() const
{
    return m_name;
}

Route* Mission::route() const
{
    return m_route;
}

void Mission::setVehicle(const QString& vehicle)
{
    if (m_vehicle == vehicle)
        return;

    m_vehicle = vehicle;
    emit vehicleChanged(vehicle);
}

void Mission::setName(const QString& name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void Mission::setRoute(Route* route)
{
    if (m_route == route)
        return;

    m_route = route;
    emit routeChanged(route);
}
