#include "module_vegur.h"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlEngine>

#include "locator.h"
#include "missions_controller.h"

using namespace md::app;

void registerTypes()
{
    qRegisterMetaType<md::domain::MissionStatus>("MissionStatus");

    qmlRegisterType<md::presentation::MissionsController>("Dreka.Vegur", 1, 0, "MissionsController");
}

Q_COREAPP_STARTUP_FUNCTION(registerTypes);

ModuleVegur::ModuleVegur()
{
}

ModuleVegur::~ModuleVegur()
{
    Locator::unprovide<domain::IMissionsService>();
}

void ModuleVegur::visit(QJsonObject& features)
{
    md::utils::insertInArray(features, "menu", "qrc:/Vegur/Vegur.qml");
}
