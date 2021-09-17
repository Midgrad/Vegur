#include "missions_service.h"

#include <QDebug>

#include "utils.h"

using namespace md::domain;

MissionsService::MissionsService(data_source::IJsonGateway* repository, QObject* parent) :
    IMissionsService(parent),
    m_repository(repository)
{
    m_repository->setParent(this);
}

QList<Mission*> MissionsService::missions() const
{
    return m_missions.values();
}

QStringList MissionsService::missionTypes() const
{
    return m_missionFactories.keys();
}

void MissionsService::registerMissionType(const QString& type, IMissionFactory* factory)
{
    if (m_missionFactories.contains(type))
        qCritical() << "Factory registration with existing type name!";

    m_missionFactories.insert(type, factory);
    this->readAllMissions();
}

void MissionsService::readAllMissions()
{
    for (const QVariant& id : m_repository->selectIds())
    {
        QJsonObject json = m_repository->read(id);
        QString type = json.value(params::type).toString();

        domain::Mission* mission = nullptr;
        if (m_missions.contains(id))
        {
            mission = m_missions.value(id);
        }
        else
        {
            IMissionFactory* factory = m_missionFactories.value(type, nullptr);
            if (!factory)
            {
                qWarning() << "No mission factory for type" << type;
                continue;
            }
            mission = factory->createMission(json.value(params::name).toString());
            m_missions[id] = mission;
            mission->setParent(this);
            emit missionAdded(mission);
        }
        mission->fromJson(json);
    }
}

void MissionsService::createMission(const QString& type)
{
    IMissionFactory* factory = m_missionFactories.value(type, nullptr);
    if (!factory)
    {
        qWarning() << "No mission factory for type" << type;
        return;
    }

    QStringList names;
    for (Mission* mission : qAsConst(m_missions))
    {
        names += mission->name();
    }
    QString name = utils::nameFromType(type, names);
    this->saveMission(factory->createMission(name));
}

void MissionsService::removeMission(Mission* mission)
{
    if (!mission->id().isNull())
        m_repository->remove(mission->id());

    if (m_missions.contains(mission->id()))
        m_missions.remove(mission->id());

    emit missionRemoved(mission);
    mission->deleteLater();
}

void MissionsService::restoreMission(Mission* mission)
{
    if (mission->id().isNull())
        return;

    QJsonObject json = m_repository->read(mission->id());
    if (!json.isEmpty())
        mission->fromJson(json);
}

void MissionsService::saveMission(Mission* mission)
{
    if (mission->id().isNull())
    {
        qWarning() << "Can't save mission with no id" << mission;
        return;
    }

    m_repository->save(mission->id(), mission->toJson());

    if (!m_missions.contains(mission->id()))
    {
        m_missions[mission->id()] = mission;
        mission->setParent(this);
        emit missionAdded(mission);
    }
}
