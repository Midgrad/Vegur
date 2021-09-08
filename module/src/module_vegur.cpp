#include "module_vegur.h"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlEngine>

#include "i_property_tree.h"
#include "locator.h"
#include "missions_controller.h"
#include "missions_service.h"
#include "routes_controller.h"

using namespace md::app;

void registerTypes()
{
    qmlRegisterType<md::presentation::RoutesController>("Dreka.Vegur", 1, 0, "RoutesController");
    qmlRegisterType<md::presentation::MissionsController>("Dreka.Vegur", 1, 0, "MissionsController");
}

Q_COREAPP_STARTUP_FUNCTION(registerTypes);

ModuleVegur::ModuleVegur()
{
    Locator::provide<domain::IMissionsService>(new domain::MissionsService(this));
}

ModuleVegur::~ModuleVegur()
{
    Locator::unprovide<domain::IMissionsService>();
}

void ModuleVegur::visit(QJsonObject& features)
{
    md::utils::insertInArray(features, "menu", "qrc:/Vegur/MissionsView.qml");
    md::utils::insertInArray(features, "menu", "qrc:/Vegur/RoutesView.qml");
}
