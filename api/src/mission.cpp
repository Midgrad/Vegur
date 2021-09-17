#include "mission.h"

using namespace md::domain;

Mission::Mission(const QString& type, const QVariant& id, const QString& name, QObject* parent) :
    Entity(id, name, parent),
    m_type(type)
{
}

QJsonObject Mission::toJson() const
{
    QJsonObject json = Entity::toJson();

    json.insert(params::type, m_type);
    json.insert(params::vehicle, m_vehicle);

    if (m_route)
        json.insert(params::route, m_route->toJson());

    return json;
}

void Mission::fromJson(const QJsonObject& json)
{
    Entity::fromJson(json);
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

bool Mission::isComplete() const
{
    return m_progress >= m_total;
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

void Mission::setProgress(int progress)
{
    if (m_progress == progress)
        return;

    bool complete = this->isComplete();

    m_progress = progress;
    emit progressChanged();

    if (complete != this->isComplete())
        emit completeChanged();
}

void Mission::setTotal(int total)
{
    if (m_total == total)
        return;

    bool complete = this->isComplete();

    m_total = total;
    emit totalChanged();

    if (complete != this->isComplete())
        emit completeChanged();
}
