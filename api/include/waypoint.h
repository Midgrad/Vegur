#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "entity.h"
#include "waypoint_type.h"

namespace md::domain
{
class Waypoint : public Entity
{
    Q_OBJECT

public:
    explicit Waypoint(const WaypointType* type, QObject* parent = nullptr);

    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& json) override;

    const WaypointType* type() const;

public slots:
    void setType(const WaypointType* type);
    void syncParameters();
    void resetParameter(const QString& key);

signals:
    void typeChanged();

private:
    const WaypointType* m_type;
};
} // namespace md::domain

#endif // WAYPOINT_H
