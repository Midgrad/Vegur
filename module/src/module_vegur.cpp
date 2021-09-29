#include "module_vegur.h"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlEngine>

#include "json_gateway_files.h"
#include "locator.h"
#include "missions_controller.h"
#include "missions_service.h"

namespace
{
constexpr char missionsFolder[] = "./missions";
}

using namespace md::app;

void registerTypes()
{
    qRegisterMetaType<md::domain::MissionStatus>("MissionStatus");

    qmlRegisterType<md::presentation::MissionsController>("Dreka.Vegur", 1, 0, "MissionsController");
}

Q_COREAPP_STARTUP_FUNCTION(registerTypes);

ModuleVegur::ModuleVegur()
{
    auto missionsService = new domain::MissionsService(new data_source::JsonGatewayFiles(
                                                           ::missionsFolder),
                                                       this);
    missionsService->readAllMissions();

    Locator::provide<domain::IMissionsService>(missionsService);
}

ModuleVegur::~ModuleVegur()
{
    Locator::unprovide<domain::IMissionsService>();
}

void ModuleVegur::visit(QJsonObject& features)
{
    md::utils::insertInArray(features, "menu", "qrc:/Vegur/MissionListView.qml");
}
