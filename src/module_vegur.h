#ifndef MODULE_VEGUR_H
#define MODULE_VEGUR_H

#include "i_module.h"

namespace draken::app
{
class ModuleVegur
    : public QObject
    , public kjarni::app::IModule
{
    Q_OBJECT
    Q_INTERFACES(kjarni::app::IModule)
    Q_PLUGIN_METADATA(IID "Midgrad.ModuleVegur" FILE "meta.json")

public:
    Q_INVOKABLE ModuleVegur();

    void visit(QJsonObject& features) override;
};
} // namespace draken::app

#endif // MODULE_VEGUR_H
