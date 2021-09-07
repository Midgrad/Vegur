#include "module_vegur.h"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlEngine>

#include "routes_controller.h"

using namespace md::app;

void registerTypes()
{
    qmlRegisterType<md::presentation::RoutesController>("Dreka.Vegur", 1, 0, "RoutesController");
}

Q_COREAPP_STARTUP_FUNCTION(registerTypes);

ModuleVegur::ModuleVegur()
{
}

void ModuleVegur::visit(QJsonObject& features)
{
    md::utils::insertInArray(features, "menu", "qrc:/Vegur/RoutesView.qml");
}
