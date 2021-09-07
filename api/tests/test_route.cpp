#include <gtest/gtest.h>

#include <QSignalSpy>

#include "route.h"

using namespace md::domain;

class RouteTest : public ::testing::Test
{
public:
    RouteTest()
    {
    }

    Route route;
};

TEST_F(RouteTest, testAddWaypoints)
{
    QSignalSpy addSpy(&route, &Route::waypointAdded);

    Waypoint wpt1;
    Waypoint wpt2;

    route.addWaypoint(&wpt1);

    EXPECT_EQ(addSpy.count(), 1);
    EXPECT_TRUE(route.waypoins().contains(&wpt1));
    EXPECT_FALSE(route.waypoins().contains(&wpt2));

    route.addWaypoint(&wpt2);

    EXPECT_EQ(addSpy.count(), 2);
    EXPECT_TRUE(route.waypoins().contains(&wpt1));
    EXPECT_TRUE(route.waypoins().contains(&wpt2));
}

TEST_F(RouteTest, testRemoveWaypoints)
{
    QSignalSpy removeSpy(&route, &Route::waypointRemoved);

    Waypoint wpt1;
    Waypoint wpt2;

    route.addWaypoint(&wpt1);
    route.addWaypoint(&wpt2);

    route.removeWaypoint(&wpt2);

    EXPECT_EQ(removeSpy.count(), 1);
    EXPECT_TRUE(route.waypoins().contains(&wpt1));
    EXPECT_FALSE(route.waypoins().contains(&wpt2));

    route.removeWaypoint(&wpt1);

    EXPECT_EQ(removeSpy.count(), 2);
    EXPECT_FALSE(route.waypoins().contains(&wpt1));
    EXPECT_FALSE(route.waypoins().contains(&wpt2));
}
