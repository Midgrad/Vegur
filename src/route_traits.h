#ifndef ROUTE_TRAITS_H
#define ROUTE_TRAITS_H

#include "kjarni_traits.h"

namespace md::domain
{
namespace route_params
{
constexpr char name[] = "name";
constexpr char type[] = "type";
constexpr char initial[] = "initial";
constexpr char waypoints[] = "waypoints";
} // namespace route_params

namespace route_features
{
constexpr char bannedNames[] = "bannedNames";
constexpr char centerPosition[] = "$CENTER_COORDINATE";
} // namespace route_features
} // namespace md::domain

#endif // ROUTE_TRAITS_H
