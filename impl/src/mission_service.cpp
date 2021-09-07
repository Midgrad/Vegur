#include "mission_service.h"

using namespace md::domain;

MissionService::MissionService(QObject* parent) : IMissionService(parent)
{
}

QList<Mission*> MissionService::missions() const
{
    return m_missions;
}

void MissionService::addMission(Mission* mission)
{
    if (m_missions.contains(mission))
        return;

    if (!mission->parent())
        mission->setParent(this);

    m_missions.append(mission);
    emit missionAdded(mission);
}

void MissionService::removeMission(Mission* mission)
{
    if (!m_missions.contains(mission))
        return;

    if (mission->parent() == this)
        mission->setParent(nullptr);

    m_missions.removeOne(mission);
    emit missionRemoved(mission);
}
