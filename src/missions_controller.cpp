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
    connect(m_missionsService, &IMissionsService::missionTypesChanged, this,
            &MissionsController::missionTypesChanged);
    connect(m_missionsService, &IMissionsService::missionAdded, this,
            &MissionsController::missionsChanged);
    connect(m_missionsService, &IMissionsService::missionRemoved, this,
            &MissionsController::missionsChanged);
    connect(m_missionsService, &IMissionsService::missionChanged, this, [this](Mission* mission) {
        emit missionChanged(mission->id());
    });
    connect(m_missionsService, &IMissionsService::statusUpdated, this,
            [this](const QVariant& missionId, const MissionStatus& status) {
                emit missionStatusChanged(missionId, status.toJson());
            });
}

QStringList MissionsController::vehicles() const
{
    // TODO: vehicles only
    QStringList result = m_pTree->rootNodes();
    result.prepend(QString());
    return result;
}

QVariantList MissionsController::missions() const
{
    return m_missionsService->missionIds();
}

QStringList MissionsController::missionTypes() const
{
    QStringList missionTypes;
    for (auto missionType : m_missionsService->missionTypes())
    {
        missionTypes += missionType->name;
    }
    return missionTypes;
}

QJsonObject MissionsController::mission(const QVariant& missionId) const
{
    Mission* mission = m_missionsService->mission(missionId);
    if (!mission)
        return QJsonObject();

    return mission->toJson(true);
}

QJsonObject MissionsController::missionStatus(const QVariant& missionId) const
{
    return m_missionsService->status(missionId).toJson();
}

QJsonObject MissionsController::route(const QVariant& missionId) const
{
    Mission* mission = m_missionsService->mission(missionId);
    if (!mission)
        return QJsonObject();

    return mission->route()->toJson(true);
}

void MissionsController::addNewMission(const QString& missionType)
{
    m_missionsService->createMission(missionType);
}

void MissionsController::saveMission(const QVariant& missionId, const QJsonObject& data)
{
    Mission* mission = m_missionsService->mission(missionId);
    if (!mission)
        return;

    mission->fromJson(data);
    m_missionsService->saveMission(mission);
}

void MissionsController::remove(const QVariant& missionId)
{
    Mission* mission = m_missionsService->mission(missionId);
    if (!mission)
        return;

    m_missionsService->removeMission(mission);
}

void MissionsController::assign(const QVariant& missionId, const QString& vehicle)
{
    Mission* mission = m_missionsService->mission(missionId);
    if (!mission)
        return;

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

void MissionsController::upload(const QVariant& missionId)
{
    Mission* mission = m_missionsService->mission(missionId);
    if (!mission)
        return;

    emit m_missionsService->upload(mission);
}

void MissionsController::download(const QVariant& missionId)
{
    Mission* mission = m_missionsService->mission(missionId);
    if (!mission)
        return;

    emit m_missionsService->download(mission);
}

void MissionsController::cancel(const QVariant& missionId)
{
    Mission* mission = m_missionsService->mission(missionId);
    if (!mission)
        return;

    emit m_missionsService->cancel(mission);
}
