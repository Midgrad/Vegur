#include "module_vegur.h"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlEngine>

#include "routes_controller.h"

using namespace vegur::app;

void registerTypes()
{
    qmlRegisterType<vegur::endpoint::RoutesController>("Dreka.Vegur", 1, 0, "RoutesController");
}

Q_COREAPP_STARTUP_FUNCTION(registerTypes);

ModuleVegur::ModuleVegur()
{
}

void ModuleVegur::visit(QJsonObject& features)
{
    kjarni::utils::insertInArray(features, "menu", "qrc:/Vegur/RoutesView.qml");
}
