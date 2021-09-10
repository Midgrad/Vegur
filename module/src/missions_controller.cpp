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

QAbstractListModel* MissionsController::missions()
{
    return &m_missionsModel;
}

QStringList MissionsController::vehicles() const
{
    // TODO: vehicles only
    QStringList result = m_pTree->rootNodes();
    result.prepend(QString());
    return result;
}

void MissionsController::addNewMission(const QString& vehicleId)
{
    auto mission = new Mission("mission_id", "New Mission");
    mission->setVehicle(vehicleId);

    m_missionsService->addMission(mission);
}

void MissionsController::removeMission(domain::Mission* mission)
{
    m_missionsService->removeMission(mission);
}
