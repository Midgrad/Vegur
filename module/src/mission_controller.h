#ifndef MISSION_CONTROLLER_H
#define MISSION_CONTROLLER_H

#include "i_missions_service.h"
#include "i_property_tree.h"

namespace md::presentation
{
class MissionController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList vehicles READ vehicles NOTIFY vehiclesChanged)
    Q_PROPERTY(QVariant missionId READ missionId WRITE setMissionId NOTIFY missionChanged)
    Q_PROPERTY(QJsonObject mission READ mission NOTIFY missionChanged)

    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(int total READ total NOTIFY totalChanged)
    Q_PROPERTY(bool complete READ isComplete NOTIFY completeChanged)

public:
    explicit MissionController(QObject* parent = nullptr);

    QStringList vehicles() const;
    QVariant missionId() const;
    QJsonObject mission() const;

    int progress() const;
    int total() const;
    bool isComplete() const;

public slots:
    void setMissionId(const QVariant& missionId);

    void save();
    void remove();
    void assign(const QString& vehicle);
    void upload();
    void download();
    void cancel();

signals:
    void vehiclesChanged();
    void missionChanged();

    void progressChanged();
    void totalChanged();
    void completeChanged();

private:
    domain::IMissionsService* const m_missionsService;
    domain::IPropertyTree* const m_pTree;
    domain::Mission* m_mission = nullptr;
};
} // namespace md::presentation

#endif // MISSION_CONTROLLER_H
