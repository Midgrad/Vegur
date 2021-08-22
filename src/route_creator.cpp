#include "route_creator.h"

#include <QJsonArray>

#include "route_traits.h"
#include "utils.h"

using namespace kjarni::domain;
using namespace vegur::domain;

RouteCreator::RouteCreator(const QJsonObject& type, const QVariantMap& features) :
    m_type(type),
    m_features(features)
{
}

QJsonObject RouteCreator::create()
{
    QJsonObject route;
    QStringList bannedNames = m_features.value(route_features::bannedNames).toStringList();
    route[kjarni_params::name] =
        kjarni::utils::nameFromType(m_type.value(kjarni_params::name).toString(), bannedNames);
    route[route_params::type] = m_type.value(kjarni_params::id);

    // Initial route template
    QJsonArray waypoints;
    for (const QJsonValue& value : m_type.value(route_params::initial).toArray())
    {
        QJsonObject waypoint;
        QJsonObject source = value.toObject();
        if (source.isEmpty())
            continue;

        waypoint[kjarni_params::name] = source.value(kjarni_params::name).toString();
        waypoint[route_params::type] = source.value(route_params::type).toString();

        // Set deafult params
        for (const QJsonValue& jsonValue : source.value(kjarni_params::params).toArray())
        {
            QJsonObject param = jsonValue.toObject();
            if (param.isEmpty())
                continue;

            QJsonValue value = param.value(kjarni_params::value);

            // Try mask params
            for (const QString& mask : m_features.keys())
            {
                if (value.toString() == mask)
                    value = QJsonValue::fromVariant(m_features.value(mask));
            }

            waypoint[param.value(kjarni_params::id).toString()] = value;
        }

        waypoints.append(waypoint);
    }

    route.insert(route_params::waypoints, waypoints);

    return route;
}
