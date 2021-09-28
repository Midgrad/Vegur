#ifndef MISSION_LIST_CONTROLLER_H
#define MISSION_LIST_CONTROLLER_H

#include <QJsonArray>

#include "i_missions_service.h"

namespace md::presentation
{
class MissionListController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QJsonArray missions READ missions NOTIFY missionsChanged)
    Q_PROPERTY(QStringList missionTypes READ missionTypes NOTIFY missionTypesChanged)

public:
    explicit MissionListController(QObject* parent = nullptr);

    QJsonArray missions() const;
    QStringList missionTypes() const;

public slots:
    void addNewMission(const QString& missionType);

signals:
    void missionsChanged();
    void missionTypesChanged();

private:
    domain::IMissionsService* const m_missionsService;
};
} // namespace md::presentation

#endif // MISSION_LIST_CONTROLLER_H
