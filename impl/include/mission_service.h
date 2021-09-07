#ifndef MISSION_SERVICE_H
#define MISSION_SERVICE_H

#include "i_mission_service.h"

namespace md::domain
{
class MissionService : public IMissionService
{
    Q_OBJECT

public:
    explicit MissionService(QObject* parent = nullptr);

    QList<Mission*> missions() const override;

public slots:
    void addMission(Mission* mission) override;
    void removeMission(Mission* mission) override;

private:
    QList<Mission*> m_missions;
};
} // namespace md::domain

#endif // MISSION_SERVICE_H
