#ifndef I_MISSIONS_SERVICE_H
#define I_MISSIONS_SERVICE_H

#include "i_mission_factory.h"
#include "i_service.h"

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
    virtual QStringList missionTypes() const = 0;

    virtual void registerMissionType(const QString& type, IMissionFactory* factory) = 0;

public slots:
    virtual void readAllMissions() = 0;
    virtual void createMission(const QString& type) = 0;
    virtual void removeMission(Mission* mission) = 0;
    virtual void restoreMission(Mission* mission) = 0;
    virtual void saveMission(Mission* mission) = 0;

signals:
    void missionAdded(Mission* mission);
    void missionRemoved(Mission* mission);
};
} // namespace md::domain

#endif // I_MISSIONS_SERVICE_H
