#ifndef I_MISSIONS_SERVICE_H
#define I_MISSIONS_SERVICE_H

#include "i_service.h"
#include "mission.h"

namespace md::domain
{
class IMissionsService
    : public QObject
    , public IService
{
    Q_OBJECT

public:
    IMissionsService(QObject* parent) : QObject(parent), IService()
    {
    }

    virtual QList<Mission*> missions() const = 0;
    virtual QList<MissionType> missionTypes() const = 0;

public slots:
    virtual void addMission(Mission* mission) = 0;
    virtual void removeMission(Mission* mission) = 0;

    virtual void addMissionType(const MissionType& missionType) = 0;
    virtual void removeMissionType(const MissionType& missionType) = 0;

signals:
    void missionAdded(Mission* mission);
    void missionRemoved(Mission* mission);

    void missionTypeAdded(MissionType* mission);
    void missionTypeRemoved(MissionType* mission);
};
} // namespace md::domain

#endif // I_MISSIONS_SERVICE_H
