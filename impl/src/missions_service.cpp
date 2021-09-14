#include "missions_service.h"

#include <QDebug>

using namespace md::domain;

MissionsService::MissionsService(QObject* parent) : IMissionsService(parent)
{
}

QList<Mission*> MissionsService::missions() const
{
    return m_missions;
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
}

void MissionsService::createMission(const QString& type)
{
    IMissionFactory* factory = m_missionFactories.value(type, nullptr);
    if (!factory)
    {
        emit errored(tr("Invalid mission type"));
        return;
    }

    Mission* mission = factory->create();
    mission->setParent(this);

    m_missions.append(mission);
    emit missionAdded(mission);
}

void MissionsService::removeMission(Mission* mission)
{
    if (!m_missions.contains(mission))
        return;

    m_missions.removeOne(mission);
    emit missionRemoved(mission);

    mission->deleteLater();
}

void MissionsService::saveMission(Mission* mission)
{
    // TODO: save
}
