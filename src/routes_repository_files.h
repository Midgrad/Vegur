#ifndef ROUTES_REPOSITORY_FILES_H
#define ROUTES_REPOSITORY_FILES_H

#include "i_routes_repository.h"

#include <QDir>
#include <QFileSystemWatcher>
#include <QMap>

namespace vegur::domain
{
class RoutesRepositoryFiles : public IRoutesRepository
{
    Q_OBJECT

public:
    RoutesRepositoryFiles(const QString& path, QObject* parent = nullptr);

    QList<QJsonObject> routes() const override;
    QJsonObject route(const QString& routeId) const override;

    void saveRoute(const QJsonObject& routeData) override;
    void removeRoute(const QString& routeId) override;

private slots:
    void scanRoutes();

private:
    const QDir m_dir;
    QFileSystemWatcher m_watcher;
    QMap<QString, QJsonObject> m_routes;
};
} // namespace vegur::domain

#endif // ROUTES_REPOSITORY_FILES_H
