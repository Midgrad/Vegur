#ifndef ROUTES_CONTROLLER_H
#define ROUTES_CONTROLLER_H

#include "i_routes_repository.h"

namespace vegur::endpoint
{
class RoutesController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList routes READ routes NOTIFY routesChanged)

public:
    explicit RoutesController(QObject* parent = nullptr);

    QStringList routes() const;

public slots:
    void filter(const QString& filterString);

    void createRoute(const QString& name);
    void removeRoute(const QString& name);

signals:
    void routesChanged();

private:
    QString m_filterString;
    domain::IRoutesRepository* const m_repository;
};
} // namespace vegur::endpoint

#endif // ROUTES_CONTROLLER_H
