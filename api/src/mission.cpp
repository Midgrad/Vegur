#include "mission.h"

using namespace md::domain;

Mission::Mission(const QString& type, const QString& name, QObject* parent) :
    Entity(name, parent),
    m_type(type)
{
}

QString Mission::type() const
{
    return m_type;
}

QString Mission::vehicle() const
{
    return m_vehicle;
}

Route* Mission::route() const
{
    return m_route;
}

int Mission::progress() const
{
    return m_progress;
}

int Mission::total() const
{
    return m_total;
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

    if (route->thread() != this->thread())
        route->moveToThread(this->thread());

    if (!route->parent())
        route->setParent(this);

    m_route = route;
    emit routeChanged(route);
}

void Mission::setProgres(int progress)
{
    if (m_progress == progress)
        return;

    m_progress = progress;
    emit progressChanged();
}

void Mission::setTotal(int total)
{
    if (m_total == total)
        return;

    m_total = total;
    emit totalChanged();
}
