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

ModuleVegur::ModuleVegur() :
    m_missionService(
        new domain::MissionsService(new data_source::JsonGatewayFiles(::missionsFolder), this))
{
    Locator::provide<domain::IMissionsService>(m_missionService);
}

ModuleVegur::~ModuleVegur()
{
    Locator::unprovide<domain::IMissionsService>();
}

void ModuleVegur::start()
{
    m_missionService->readAllMissions();
}

void ModuleVegur::visit(QJsonObject& features)
{
    md::utils::insertInArray(features, "menu", "qrc:/Vegur/Vegur.qml");
}
