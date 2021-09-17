#ifndef MISSIONS_SERVICE_H
#define MISSIONS_SERVICE_H

#include "i_json_gateway.h"
#include "i_missions_service.h"

namespace md::domain
{
class MissionsService : public IMissionsService
{
    Q_OBJECT

public:
    explicit MissionsService(data_source::IJsonGateway* repository, QObject* parent = nullptr);

    QList<Mission*> missions() const override;
    QStringList missionTypes() const override;

    void registerMissionType(const QString& type, IMissionFactory* factory) override;

public slots:
    void readAllMissions() override;
    void createMission(const QString& type) override;
    void removeMission(Mission* mission) override;
    void restoreMission(Mission* mission) override;
    void saveMission(Mission* mission) override;

private:
    data_source::IJsonGateway* const m_repository;
    QMap<QString, IMissionFactory*> m_missionFactories;
    QMap<QVariant, Mission*> m_missions;
};
} // namespace md::domain

#endif // MISSIONS_SERVICE_H
