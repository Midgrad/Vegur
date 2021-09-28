#ifndef MISSION_H
#define MISSION_H

#include "route.h"

namespace md::domain
{
class Mission : public Entity
{
    Q_OBJECT

public:
    Mission(const QString& type, const QVariant& id, const QString& name, QObject* parent = nullptr);
    Mission(const QJsonObject& json, QObject* parent = nullptr);

    QJsonObject toJson(bool recursive) const override;
    void fromJson(const QJsonObject& json) override;

    QString type() const;
    QString vehicle() const;
    Route* route() const;

    int progress() const;
    int total() const;
    bool isComplete() const;

public slots:
    void setVehicle(const QString& vehicle);

    void setProgress(int progress);
    void setTotal(int total);

signals:
    void vehicleChanged(QString vehicle);
    void routeChanged(Route* route);

    void progressChanged();
    void totalChanged();
    void completeChanged();

private:
    const QString m_type;
    QString m_vehicle;
    Route* const m_route;

    int m_progress = 0;
    int m_total = 0;
};
} // namespace md::domain

#endif // MISSION_H
