#include "routes_repository_files.h"

#include <QDebug>
#include <QJsonDocument>

#include "utils.h"

using namespace vegur::domain;

RoutesRepositoryFiles::RoutesRepositoryFiles(const QString& path, QObject* parent) :
    IRoutesRepository(parent),
    m_dir(path)
{
    if (!m_dir.exists())
        m_dir.mkpath(".");

    m_watcher.addPath(m_dir.path());
    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this,
            &RoutesRepositoryFiles::scanRoutes);

    this->scanRoutes();
}

QList<QJsonObject> RoutesRepositoryFiles::routes() const
{
    return m_routes.values();
}

QJsonObject RoutesRepositoryFiles::route(const QString& routeId) const
{
    return m_routes.value(routeId);
}

void RoutesRepositoryFiles::saveRoute(const QJsonObject& routeData)
{
    QString name = routeData.value(rote_params::name).toString();
    if (name.isEmpty())
        return;

    auto routeId = kjarni::utils::nameToFilename(name, "json");

    QFile file(m_dir.path() + "/" + routeId);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);

    QJsonObject modified(routeData);
    modified.remove(rote_params::id);

    QJsonDocument doc(modified);
    file.write(doc.toJson());
    file.close();
}

void RoutesRepositoryFiles::removeRoute(const QString& routeId)
{
    QFile file(m_dir.path() + "/" + routeId);
    file.remove();
}

void RoutesRepositoryFiles::scanRoutes()
{
    QStringList routeIds;
    for (const QFileInfo& fileInfo : m_dir.entryList({ "*.json" }, QDir::Files))
    {
        auto routeId = fileInfo.fileName();
        QFile file(m_dir.path() + "/" + routeId);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            continue;

        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();

        QJsonObject routeData = doc.object();
        if (routeData.isEmpty())
            continue;

        routeIds += routeId;
        routeData.insert(rote_params::id, routeId);

        bool isNew = !m_routes.contains(routeId);

        m_routes[routeId] = routeData;

        emit isNew ? routeAdded(routeId) : routeChanged(routeId);
    }

    for (const QString& routeId : m_routes.keys())
    {
        if (routeIds.contains(routeId))
            continue;

        m_routes.remove(routeId);
        emit routeRemoved(routeId);
    }
    emit routesChanged();
}
