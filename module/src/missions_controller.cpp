#include "missions_controller.h"

#include <QDebug>

#include "locator.h"

using namespace md::domain;
using namespace md::presentation;

MissionsController::MissionsController(QObject* parent) :
    QObject(parent),
    m_pTree(md::app::Locator::get<IPropertyTree>()),
    m_missionsService(md::app::Locator::get<IMissionsService>())
{
    Q_ASSERT(m_pTree);
    connect(m_pTree, &IPropertyTree::rootNodesChanged, this, &MissionsController::vehiclesChanged);

    Q_ASSERT(m_missionsService);
    connect(m_missionsService, &IMissionsService::missionAdded, this, [this](Mission* mission) {
        m_missionsModel.add(mission);
    });
    connect(m_missionsService, &IMissionsService::missionRemoved, this, [this](Mission* mission) {
        m_missionsModel.remove(mission);
    });
    m_missionsModel.reset(m_missionsService->missions());
}

QAbstractListModel* MissionsController::missions() const
{
    return const_cast<EntityModel<domain::Mission>*>(&m_missionsModel);
}

QStringList MissionsController::missionTypes() const
{
    return m_missionsService->missionTypes();
}

QStringList MissionsController::vehicles() const
{
    // TODO: vehicles only
    QStringList result = m_pTree->rootNodes();
    result.prepend(QString());
    return result;
}

void MissionsController::addNewMission(const QString& missionType)
{
    m_missionsService->createMission(missionType);
}

void MissionsController::removeMission(domain::Mission* mission)
{
    m_missionsService->removeMission(mission);
}

void MissionsController::assignMission(domain::Mission* mission, const QString& vehicle)
{
    for (domain::Mission* oldMission : m_missionsService->missions())
    {
        if (oldMission->vehicle() == vehicle)
        {
            if (oldMission == mission)
                return;

            oldMission->setVehicle(QString());
            m_missionsService->saveMission(oldMission);
        }
    }

    mission->setVehicle(vehicle);
    m_missionsService->saveMission(mission);
}
