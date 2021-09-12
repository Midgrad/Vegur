#include "missions_service.h"

using namespace md::domain;

MissionsService::MissionsService(QObject* parent) : IMissionsService(parent)
{
}

QList<Mission*> MissionsService::missions() const
{
    return m_missions;
}

QList<MissionType> MissionsService::missionTypes() const
{
    return m_missionTypes;
}

void MissionsService::addMission(Mission* mission)
{
    if (m_missions.contains(mission))
        return;

    if (!mission->parent())
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

void MissionsService::addMissionType(const MissionType& missionType)
{
}

void MissionsService::removeMissionType(const MissionType& missionType)
{
}
