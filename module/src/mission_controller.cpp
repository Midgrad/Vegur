#include "mission_controller.h"

#include <QDebug>

#include "locator.h"

using namespace md::domain;
using namespace md::presentation;

MissionController::MissionController(QObject* parent) :
    QObject(parent),
    m_missionsService(md::app::Locator::get<IMissionsService>()),
    m_pTree(md::app::Locator::get<IPropertyTree>())
{
    Q_ASSERT(m_missionsService);

    Q_ASSERT(m_pTree);
    connect(m_pTree, &IPropertyTree::rootNodesChanged, this, &MissionController::vehiclesChanged);
}

QStringList MissionController::vehicles() const
{
    // TODO: vehicles only
    QStringList result = m_pTree->rootNodes();
    result.prepend(QString());
    return result;
}

QVariant MissionController::missionId() const
{
    return m_mission ? m_mission->id() : QVariant();
}

QJsonObject MissionController::mission() const
{
    return m_mission ? m_mission->toJson(true) : QJsonObject();
}

int MissionController::progress() const
{
    return m_mission ? m_mission->progress() : 0;
}

int MissionController::total() const
{
    return m_mission ? m_mission->total() : 0;
}

bool MissionController::isComplete() const
{
    return m_mission ? m_mission->isComplete() : false;
}

void MissionController::setMissionId(const QVariant& missionId)
{
    Mission* mission = m_missionsService->mission(missionId);

    if (m_mission == mission)
        return;

    if (m_mission)
    {
        disconnect(m_mission, nullptr, this, nullptr);
    }

    m_mission = mission;

    if (m_mission)
    {
        connect(m_mission, &Mission::progressChanged, this, &MissionController::progressChanged);
        connect(m_mission, &Mission::totalChanged, this, &MissionController::totalChanged);
        connect(m_mission, &Mission::completeChanged, this, &MissionController::completeChanged);

        emit progressChanged();
        emit totalChanged();
        emit completeChanged();
    }

    emit missionChanged();
}

void MissionController::save()
{
    if (!m_mission)
        return;

    m_missionsService->saveMission(m_mission);
}

void MissionController::remove()
{
    if (!m_mission)
        return;

    m_missionsService->removeMission(m_mission);
}

void MissionController::assign(const QString& vehicle)
{
    if (!m_mission)
        return;

    for (domain::Mission* oldMission : m_missionsService->missions())
    {
        if (oldMission->vehicle() == vehicle)
        {
            if (oldMission == m_mission)
                return;

            oldMission->setVehicle(QString());
            m_missionsService->saveMission(oldMission);
        }
    }

    m_mission->setVehicle(vehicle);
    m_missionsService->saveMission(m_mission);
}

void MissionController::upload()
{
    if (!m_mission)
        return;

    emit m_missionsService->upload(m_mission);
}

void MissionController::download()
{
    qDebug() << "download" << m_mission;
    if (!m_mission)
        return;

    emit m_missionsService->download(m_mission);
}

void MissionController::cancel()
{
    if (!m_mission)
        return;

    emit m_missionsService->cancel(m_mission);
}
