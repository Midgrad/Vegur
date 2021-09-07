#ifndef I_MISSION_SERVICE_H
#define I_MISSION_SERVICE_H

#include "mission.h"

namespace md::domain
{
class IMissionService : public QObject
{
    Q_OBJECT

public:
    IMissionService(QObject* parent) : QObject(parent)
    {
    }

    virtual QList<Mission*> missions() const = 0;

public slots:
    virtual void addMission(Mission* mission) = 0;
    virtual void removeMission(Mission* mission) = 0;

signals:
    void missionAdded(Mission* mission);
    void missionRemoved(Mission* mission);
};
} // namespace md::domain

#endif // I_MISSION_SERVICE_H
