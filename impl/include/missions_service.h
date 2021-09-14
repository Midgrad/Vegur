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
    QStringList missionTypes() const override;

    void registerMissionType(const QString& type, IMissionFactory* factory) override;

public slots:
    void createMission(const QString& type) override;
    void removeMission(Mission* mission) override;
    void saveMission(Mission* mission) override;

private:
    QList<Mission*> m_missions;
    QMap<QString, IMissionFactory*> m_missionFactories;
};
} // namespace md::domain

#endif // MISSIONS_SERVICE_H
