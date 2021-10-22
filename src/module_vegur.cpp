#include "module_vegur.h"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlEngine>

#include "i_gui_layout.h"
#include "locator.h"

using namespace md::app;

void registerTypes()
{
    qRegisterMetaType<md::domain::MissionStatus>("MissionStatus");
}

Q_COREAPP_STARTUP_FUNCTION(registerTypes);

ModuleVegur::ModuleVegur()
{
}

ModuleVegur::~ModuleVegur()
{
    Locator::unprovide<domain::IMissionsService>();
}

void ModuleVegur::init()
{
    Locator::get<presentation::IGuiLayout>()->addItem("menu", "qrc:/Vegur/Vegur.qml");
}
