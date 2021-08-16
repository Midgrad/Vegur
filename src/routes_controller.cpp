#include "routes_controller.h"

#include <QDebug>

#include "i_property_tree.h"
#include "locator.h"

namespace
{
constexpr char adsb[] = "adsb";
}

using namespace kjarni::domain;
using namespace draken::endpoint;

RoutesController::RoutesController(QObject* parent) : QObject(parent)
{
    // FIXME: demonstration routes
}

QJsonArray RoutesController::routes() const
{
    return m_routes;
}
