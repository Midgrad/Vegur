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

public slots:
    void addMission(Mission* mission) override;
    void removeMission(Mission* mission) override;

private:
    QList<Mission*> m_missions;
};
} // namespace md::domain

#endif // MISSIONS_SERVICE_H
