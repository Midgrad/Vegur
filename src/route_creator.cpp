#include "route_creator.h"

#include <QJsonArray>

#include "route_traits.h"
#include "utils.h"

using namespace md::domain;

RouteCreator::RouteCreator(const QJsonObject& type, const QVariantMap& features) :
    m_type(type),
    m_features(features)
{
}

QJsonObject RouteCreator::create()
{
    QJsonObject route;
    QStringList bannedNames = m_features.value(route_features::bannedNames).toStringList();
    route[params::name] = md::utils::nameFromType(m_type.value(params::name).toString(),
                                                  bannedNames);
    route[route_params::type] = m_type.value(params::id);

    // Initial route template
    QJsonArray waypoints;
    for (const QJsonValue& value : m_type.value(route_params::initial).toArray())
    {
        QJsonObject waypoint;
        QJsonObject source = value.toObject();
        if (source.isEmpty())
            continue;

        waypoint[params::name] = source.value(params::name).toString();
        waypoint[route_params::type] = source.value(route_params::type).toString();

        // Set deafult params
        for (const QJsonValue& jsonValue : source.value(params::params).toArray())
        {
            QJsonObject param = jsonValue.toObject();
            if (param.isEmpty())
                continue;

            QJsonValue value = param.value(params::value);

            // Try mask params
            for (const QString& mask : m_features.keys())
            {
                if (value.toString() == mask)
                    value = QJsonValue::fromVariant(m_features.value(mask));
            }

            waypoint[param.value(params::id).toString()] = value;
        }

        waypoints.append(waypoint);
    }

    route.insert(route_params::waypoints, waypoints);

    return route;
}
