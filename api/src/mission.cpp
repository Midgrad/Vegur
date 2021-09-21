#include "mission.h"

using namespace md::domain;

Mission::Mission(const QString& type, const QVariant& id, const QString& name, QObject* parent) :
    Entity(id, name, parent),
    m_type(type),
    m_route(new Route(this))
{
}

Mission::Mission(const QJsonObject& json, QObject* parent) :
    Entity(json, parent),
    m_type(json.value(params::type).toString()),
    m_vehicle(json.value(params::vehicle).toString()),
    m_route(new Route(json.value(params::route).toObject(), this))
{
}

QJsonObject Mission::toJson(bool recursive) const
{
    QJsonObject json = Entity::toJson();

    json.insert(params::type, m_type);
    json.insert(params::vehicle, m_vehicle);
    if (recursive)
        json.insert(params::route, m_route->toJson(recursive));

    return json;
}

void Mission::fromJson(const QJsonObject& json)
{
    this->setVehicle(json.value(params::vehicle).toString());

    m_route->fromJson(json.value(params::route).toObject());

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
