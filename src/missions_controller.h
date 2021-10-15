#ifndef MISSIONS_CONTROLLER_H
#define MISSIONS_CONTROLLER_H

#include "i_missions_service.h"
#include "i_property_tree.h"

namespace md::presentation
{
// TODO: routes controller
class MissionsController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList vehicles READ vehicles NOTIFY vehiclesChanged)
    Q_PROPERTY(QVariantList missions READ missions NOTIFY missionsChanged)
    Q_PROPERTY(QStringList missionTypes READ missionTypes NOTIFY missionTypesChanged)

public:
    explicit MissionsController(QObject* parent = nullptr);

    QStringList vehicles() const;
    QVariantList missions() const;
    QStringList missionTypes() const;

    Q_INVOKABLE QJsonObject mission(const QVariant& missionId) const;
    Q_INVOKABLE QJsonObject missionStatus(const QVariant& missionId) const;
    Q_INVOKABLE QJsonObject route(const QVariant& missionId) const;

public slots:
    void addNewMission(const QString& missionType);
    void saveMission(const QVariant& missionId, const QJsonObject& data);
    void remove(const QVariant& missionId);
    void upload(const QVariant& missionId);
    void download(const QVariant& missionId);
    void cancel(const QVariant& missionId);

signals:
    void vehiclesChanged();
    void missionsChanged();
    void missionTypesChanged();

    void missionChanged(QVariant missionId);
    void missionStatusChanged(QVariant missionId, QJsonObject status);
    void routeChanged(QVariant missionId);

    void centerRoute(QVariant missionId);
    void editRoute(QVariant missionId);
    void centerWaypoint(QVariant missionId, int index);

private slots:
    void onMissionAdded(domain::Mission* mission);
    void onMissionRemoved(domain::Mission* mission);

private:
    domain::IPropertyTree* const m_pTree;
    domain::IMissionsService* const m_missionsService;
};
} // namespace md::presentation

#endif // MISSIONS_CONTROLLER_H
