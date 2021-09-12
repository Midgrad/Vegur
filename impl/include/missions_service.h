#ifndef MISSIONS_SERVICE_H
#define MISSIONS_SERVICE_H

#include "i_missions_service.h"

namespace md::domain
{
class MissionsService : public IMissionsService
{
    Q_OBJECT

public:
    explicit MissionsService(QObject* parent = nullptr);

    QList<Mission*> missions() const override;
    QList<MissionType> missionTypes() const override;

public slots:
    void addMission(Mission* mission) override;
    void removeMission(Mission* mission) override;

    void addMissionType(const MissionType& missionType) override;
    void removeMissionType(const MissionType& missionType) override;

private:
    QList<Mission*> m_missions;
    QList<MissionType> m_missionTypes;
};
} // namespace md::domain

#endif // MISSIONS_SERVICE_H
