#include "route_creator.h"

#include <QJsonArray>

#include "route_traits.h"
#include "utils.h"

using namespace kjarni::domain;
using namespace vegur::domain;

RouteCreator::RouteCreator(const QJsonObject& type, const QStringList& bannedNames) :
    m_type(type),
    m_bannedNames(bannedNames)
{
}

QJsonObject RouteCreator::create()
{
    QJsonObject route;
    route[kjarni_params::name] =
        kjarni::utils::nameFromType(m_type.value(kjarni_params::name).toString(), m_bannedNames);
    route[route_params::type] = m_type.value(kjarni_params::id);

    QJsonArray waypoints;
    for (const QJsonValue& value : m_type.value(route_params::initial).toArray())
    {
        QJsonObject waypoint;
        QJsonObject source = value.toObject();
        if (source.isEmpty())
            continue;

        waypoint[kjarni_params::name] = source.value(kjarni_params::name).toString();
        waypoint[route_params::type] = source.value(route_params::type).toString();

        for (const QJsonValue& value : source.value(kjarni_params::params).toArray())
        {
            QJsonObject param = value.toObject();
            if (param.isEmpty())
                continue;

            waypoint[param.value(kjarni_params::id).toString()] = param.value(kjarni_params::value);
        }

        waypoints.append(waypoint);
    }

    route.insert(route_params::waypoints, waypoints);

    return route;
}
