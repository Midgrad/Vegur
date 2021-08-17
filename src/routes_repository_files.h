#ifndef ROUTES_REPOSITORY_FILES_H
#define ROUTES_REPOSITORY_FILES_H

#include "i_routes_repository.h"

#include <QDir>
#include <QFileSystemWatcher>

namespace vegur::domain
{
class RoutesRepositoryFiles : public IRoutesRepository
{
    Q_OBJECT

public:
    RoutesRepositoryFiles(const QString& path, QObject* parent = nullptr);

    QStringList routes() const override;
    QJsonObject route(const QString& route) const override;

    void saveRoute(const QString& route, const QJsonObject& data) override;
    void removeRoute(const QString& route) override;

private:
    QFileSystemWatcher m_watcher;
    const QDir m_dir;
};
} // namespace vegur::domain

#endif // ROUTES_REPOSITORY_FILES_H
