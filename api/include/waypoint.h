#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "entity.h"
#include "waypoint_type.h"

namespace md::domain
{
class Waypoint : public Entity
{
    Q_OBJECT

    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)

public:
    Waypoint(const QString& name, const QString& type, QObject* parent = nullptr);
    Waypoint(const QJsonObject& json, QObject* parent = nullptr);

    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& json) override;

    QString type() const;

public slots:
    void setType(const QString& type);

signals:
    void typeChanged();

private:
    QString m_type;
};
} // namespace md::domain

#endif // WAYPOINT_H
