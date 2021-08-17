#include "routes_repository_files.h"

#include <QDebug>
#include <QJsonDocument>

using namespace vegur::domain;

RoutesRepositoryFiles::RoutesRepositoryFiles(const QString& path, QObject* parent) :
    IRoutesRepository(parent),
    m_dir(path)
{
    if (!m_dir.exists())
        m_dir.mkpath(".");
}

QStringList RoutesRepositoryFiles::routes() const
{
    QStringList routes;
    for (const QFileInfo& fileInfo : m_dir.entryList({ ".json" }, QDir::Files))
    {
        routes.append(fileInfo.fileName());
    }
    return routes;
}

QJsonObject RoutesRepositoryFiles::route(const QString& route) const
{
    QFile file(m_dir.path() + "/" + route);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    return doc.object();
}

void RoutesRepositoryFiles::saveRoute(const QString& route, const QJsonObject& data)
{
    QFile file(m_dir.path() + "/" + route);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);

    QJsonDocument doc(data);
    file.write(doc.toJson());
    file.close();
}

void RoutesRepositoryFiles::removeRoute(const QString& route)
{
    QFile file(m_dir.path() + "/" + route);
    file.remove();
}
