#ifndef MISSIONS_CONTROLLER_H
#define MISSIONS_CONTROLLER_H

#include "entity_model.h"
#include "i_missions_service.h"
#include "i_property_tree.h"

namespace md::presentation
{
class MissionsController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QAbstractListModel* missions READ missions CONSTANT)
    Q_PROPERTY(QStringList missionTypes READ missionTypes CONSTANT)
    Q_PROPERTY(QStringList vehicles READ vehicles NOTIFY vehiclesChanged)

public:
    explicit MissionsController(QObject* parent = nullptr);

    QAbstractListModel* missions() const;
    QStringList missionTypes() const;
    QStringList vehicles() const;

public slots:
    void addNewMission(const QString& missionType);
    void saveMission(domain::Mission* mission);
    void removeMission(domain::Mission* mission);
    void assignMission(domain::Mission* mission, const QString& vehicle);

signals:
    void vehiclesChanged();

private:
    domain::IPropertyTree* const m_pTree;
    domain::IMissionsService* const m_missionsService;
    EntityModel<domain::Mission> m_missionsModel;
};
} // namespace md::presentation

#endif // MISSIONS_CONTROLLER_H
