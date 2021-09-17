#ifndef I_MISSION_FACTORY_H
#define I_MISSION_FACTORY_H

#include "mission.h"

namespace md::domain
{
class IMissionFactory
{
public:
    IMissionFactory() = default;
    virtual ~IMissionFactory() = default;

    virtual Mission* createMission(const QString& name) = 0;
};
} // namespace md::domain

#endif // I_MISSION_FACTORY_H
