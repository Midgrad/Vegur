#ifndef MISSION_H
#define MISSION_H

#include "route.h"

namespace md::domain
{
class Mission : public Entity
{
    Q_OBJECT

    Q_PROPERTY(QString type READ type CONSTANT)
    Q_PROPERTY(QString vehicle READ vehicle WRITE setVehicle NOTIFY vehicleChanged)

    Q_PROPERTY(int progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(int total READ total WRITE setTotal NOTIFY totalChanged)
    Q_PROPERTY(bool complete READ isComplete NOTIFY completeChanged)

public:
    Mission(const QString& type, const QVariant& id, const QString& name, QObject* parent = nullptr);
    Mission(const QJsonObject& json, QObject* parent = nullptr);

    Q_INVOKABLE QJsonObject toJson() const override;
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

    void upload();   // To the vehicle
    void download(); // From the vehicle
    void cancel();   // Downloading or uploading

private:
    const QString m_type;
    QString m_vehicle;
    Route* const m_route;

    int m_progress = 0;
    int m_total = 0;
};
} // namespace md::domain

#endif // MISSION_H
