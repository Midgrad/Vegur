#include "mission.h"

using namespace md::domain;

Mission::Mission(const QVariant& id, const QString& name, QObject* parent) :
    Entity(id, name, parent)
{
}

QString Mission::vehicle() const
{
    return m_vehicle;
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

void Mission::setRoute(Route* route)
{
    if (m_route == route)
        return;

    m_route = route;
    emit routeChanged(route);
}
