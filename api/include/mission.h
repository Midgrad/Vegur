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

    Q_PROPERTY(int progress READ progress WRITE setProgres NOTIFY progressChanged)
    Q_PROPERTY(int total READ total WRITE setTotal NOTIFY totalChanged)

public:
    Mission(const QString& type, const QString& name, QObject* parent = nullptr);

    QString type() const;
    QString vehicle() const;
    Route* route() const;

    int progress() const;
    int total() const;

public slots:
    void setVehicle(const QString& vehicle);
    void setRoute(Route* route);

    void setProgres(int progress);
    void setTotal(int total);

signals:
    void vehicleChanged(QString vehicle);
    void routeChanged(Route* route);

    void progressChanged();
    void totalChanged();

    void upload();   // To the vehicle
    void download(); // From the vehicle
    void cancel();   // Downloading or uploading

private:
    const QString m_type;
    QString m_vehicle;
    Route* m_route = nullptr;

    int m_progress = 0;
    int m_total = 0;
};
} // namespace md::domain

#endif // MISSION_H
