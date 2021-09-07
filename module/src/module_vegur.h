#ifndef MODULE_VEGUR_H
#define MODULE_VEGUR_H

#include "i_module.h"

namespace md::app
{
class ModuleVegur
    : public QObject
    , public md::app::IModule
{
    Q_OBJECT
    Q_INTERFACES(md::app::IModule)
    Q_PLUGIN_METADATA(IID "Midgrad.ModuleVegur" FILE "meta.json")

public:
    Q_INVOKABLE ModuleVegur();

    void visit(QJsonObject& features) override;
};
} // namespace vegur::app

#endif // MODULE_VEGUR_H
