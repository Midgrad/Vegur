#ifndef MODULE_VEGUR_H
#define MODULE_VEGUR_H

#include "i_missions_service.h"
#include "i_module.h"

namespace md::app
{
class ModuleVegur
    : public QObject
    , public IModule
{
    Q_OBJECT
    Q_INTERFACES(md::app::IModule)
    Q_PLUGIN_METADATA(IID "Midgrad.ModuleVegur" FILE "meta.json")

public:
    Q_INVOKABLE ModuleVegur();
    ~ModuleVegur() override;

    void start() override;
    void visit(QJsonObject& features) override;

private: // TODO: move to core4
    domain::IMissionsService* m_missionService = nullptr;
};
} // namespace md::app

#endif // MODULE_VEGUR_H
