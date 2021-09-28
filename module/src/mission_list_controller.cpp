#include "mission_list_controller.h"

#include <QDebug>

#include "locator.h"

using namespace md::domain;
using namespace md::presentation;

MissionListController::MissionListController(QObject* parent) :
    QObject(parent),
    m_missionsService(md::app::Locator::get<IMissionsService>())
{
    Q_ASSERT(m_missionsService);
    connect(m_missionsService, &IMissionsService::missionTypesChanged, this,
            &MissionListController::missionsChanged);
    connect(m_missionsService, &IMissionsService::missionAdded, this,
            &MissionListController::missionsChanged);
    connect(m_missionsService, &IMissionsService::missionRemoved, this,
            &MissionListController::missionsChanged);
}

QJsonArray MissionListController::missions() const
{
    QJsonArray missions;

    for (Mission* mission : m_missionsService->missions())
    {
        missions.append(mission->toJson(false));
    }

    return missions;
}

QStringList MissionListController::missionTypes() const
{
    return m_missionsService->missionTypes();
}

void MissionListController::addNewMission(const QString& missionType)
{
    m_missionsService->createMission(missionType);
}
