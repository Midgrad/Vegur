#include <gtest/gtest.h>

#include <QSignalSpy>

#include "mission.h"

using namespace md::domain;

class MissionTest : public ::testing::Test
{
public:
    MissionTest() : route("Name")
    {
    }

    Route route;
};

TEST_F(MissionTest, testRouteAddWaypoints)
{
    QSignalSpy addSpy(&route, &Route::waypointAdded);

    WaypointType type("WPT", {});

    Waypoint wpt1(&type);
    Waypoint wpt2(&type);

    route.addWaypoint(&wpt1);

    EXPECT_EQ(addSpy.count(), 1);
    EXPECT_TRUE(route.waypoints().contains(&wpt1));
    EXPECT_FALSE(route.waypoints().contains(&wpt2));

    route.addWaypoint(&wpt2);

    EXPECT_EQ(addSpy.count(), 2);
    EXPECT_TRUE(route.waypoints().contains(&wpt1));
    EXPECT_TRUE(route.waypoints().contains(&wpt2));
}

TEST_F(MissionTest, testRouteRemoveWaypoints)
{
    QSignalSpy removeSpy(&route, &Route::waypointRemoved);

    WaypointType type("WPT", {});

    Waypoint wpt1(&type);
    Waypoint wpt2(&type);

    route.addWaypoint(&wpt1);
    route.addWaypoint(&wpt2);

    route.removeWaypoint(&wpt2);

    EXPECT_EQ(removeSpy.count(), 1);
    EXPECT_TRUE(route.waypoints().contains(&wpt1));
    EXPECT_FALSE(route.waypoints().contains(&wpt2));

    route.removeWaypoint(&wpt1);

    EXPECT_EQ(removeSpy.count(), 2);
    EXPECT_FALSE(route.waypoints().contains(&wpt1));
    EXPECT_FALSE(route.waypoints().contains(&wpt2));
}
